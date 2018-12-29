#include "PlayRaidState.h"
#include "Player.h"
#include "Game.h"
#include "Engine.h"
#include "Board.h"
#include "SelectionPrompt.h"
#include "ChoicePrompt.h"
#include "ValidationPrompt.h"

PlayRaidState::PlayRaidState(Game* ipGame):GameState(ipGame), _pSelection(NULL), _raidArea(UNDEFINED_AREA),
_pChoicePrompt(NULL), _raidedArea(UNDEFINED_AREA), _pCancelOrderPrompt(NULL)
{
}

PlayRaidState::~PlayRaidState()
{
	if (NULL != _pSelection)
		delete _pSelection;
	_pSelection = NULL;

	if (NULL != _pChoicePrompt)
		delete _pChoicePrompt;
	_pChoicePrompt = NULL;

	if (NULL != _pCancelOrderPrompt)
		delete _pCancelOrderPrompt;
	_pCancelOrderPrompt = NULL;
}

L_HRESULT PlayRaidState::Init()
{
	int width = 0, height = 0;
	(_pGame->GetEngine())->GetWindowDimension(width, height);
	_pCancelOrderPrompt = new ValidationPrompt(width, height, "Annuler cet ordre ?");
	CHK_AND_RET_HR(_pCancelOrderPrompt);
	_pCancelOrderPrompt->OverrideButtonText("Annulé");
	return L_S_OK;
}

L_HRESULT PlayRaidState::Activate()
{
	_pCurrentPlayer = _pGame->GetCurrentPlayer();
	CHK_AND_RET_HR(_pCurrentPlayer);

	if(NULL == _pSelection)
		_pSelection = new SelectionPrompt(SELECTORDER, _pGame->GetBoard(), _pCurrentPlayer);
	CHK_AND_RET_HR(_pSelection);
	CHK_SUCCESS(_pSelection->Init(_pCurrentPlayer->GetAreaRaidOrders()));

	(_pGame->GetEngine())->RegisterSelectionPrompt(_pSelection);

	_Activated = true;
	return L_S_OK;
}

L_HRESULT PlayRaidState::Deactivate()
{
	_raidArea = UNDEFINED_AREA;
	_raidedArea = UNDEFINED_AREA;
	_Activated = false;
	_Completed = false;
	return L_S_OK;
}

L_HRESULT PlayRaidState::Execute()
{
	CHK_AND_RET_HR(_pCurrentPlayer);

	CHK_AND_RET_HR(_pSelection);
	if (_raidArea == UNDEFINED_AREA)
		_raidArea = _pSelection->GetSelectedArea();
	else if(_raidedArea == UNDEFINED_AREA)
		_raidedArea = _pSelection->GetSelectedArea();

	if (_pCancelOrderPrompt && _pCancelOrderPrompt->IsComplete())
	{
		_pCancelOrderPrompt->Reset();
		_pSelection->Clean();
		(_pGame->GetEngine())->UnregisterSelectionPrompt();
		(_pGame->GetEngine())->UnregisterPromptWindow();

		CHK_SUCCESS(_RemoveOrderFromArea(_raidArea));
		_Completed = true;
		return L_S_OK;
	}

	if (_pChoicePrompt )
	{
		if (!_pChoicePrompt->IsComplete())
			return L_S_OK;

		int choice = _pChoicePrompt->GetChoice();

		if (0 == choice && _raidedArea != UNDEFINED_AREA && _raidArea != UNDEFINED_AREA && _raidedArea != _raidArea)
		{
			// Test if the raided order is a consolidate order
			Board* pBoard = _pGame->GetBoard();
			CHK_AND_RET_HR(pBoard);
			BoardPiece* orderPiece = pBoard->GetElementAt(ORDERTYPE, _raidedArea);
			CHK_AND_RET_HR(orderPiece);
			ORDER orderType = (ORDER)orderPiece->GetSubType();
			if (orderType == CONSOLIDATE_1 || orderType == CONSOLIDATE_2 || orderType == CONSOLIDATE_STAR)
			{
				// The raided order is a consolidate order
				// Raiding player earns one influence token and raided player looses one
				_pCurrentPlayer->AddPowerTokens(1);

				Player* pRaided = orderPiece->GetOwner();
				CHK_AND_RET_HR(pRaided);
				pRaided->RemovePowerTokens(1);
			}

			CHK_SUCCESS(_RemoveOrderFromArea(_raidArea));

			CHK_SUCCESS(_RemoveOrderFromArea(_raidedArea));

			_Completed = true;
		}
		else
		{
			_raidedArea = UNDEFINED_AREA;
			_raidArea = UNDEFINED_AREA;
			_pSelection->Clean();

			CHK_SUCCESS(_pSelection->Init(_pCurrentPlayer->GetAreaRaidOrders()));
		}

		_pChoicePrompt->Reset();
		(_pGame->GetEngine())->UnregisterPromptWindow();

		return L_S_OK;
	}

	if (_raidedArea != UNDEFINED_AREA)
	{
		(_pGame->GetEngine())->UnregisterPromptWindow();
		_pSelection->Clean();
		if (_raidedArea == _raidArea)
		{
			CHK_SUCCESS(_pSelection->Init(_pCurrentPlayer->GetAreaRaidOrders()));
			_raidArea = UNDEFINED_AREA;
			_raidedArea = UNDEFINED_AREA;
		}
		else
		{
			(_pGame->GetEngine())->UnregisterSelectionPrompt();

			int width = 0, height = 0;
			(_pGame->GetEngine())->GetWindowDimension(width, height);
			_pChoicePrompt = new ChoicePrompt(width, height);
			CHK_AND_RET_HR(_pChoicePrompt);

			std::string choiceText = "Raid () sur l'ordre de  ()";
			_pChoicePrompt->SetText(choiceText);

			std::vector<std::pair<int, std::string>> choices;
			choices.push_back({ 0, "Confirmer" });
			choices.push_back({ 1, "Annuler" });
			_pChoicePrompt->SetChoices(choices);
			
			(_pGame->GetEngine())->RegisterPromptWindow(_pChoicePrompt);
		}
	}
	else if(_raidArea != UNDEFINED_AREA)
	{
		Board* pBoard = _pGame->GetBoard();
		CHK_AND_RET_HR(pBoard);
		BoardPiece* thisRaid = pBoard->GetElementAt(ORDERTYPE, _raidArea);
		CHK_AND_RET_HR(thisRaid);
		ORDER raidType = (ORDER)thisRaid->GetSubType();

		std::vector<AREA>::iterator it;

		// Get all the adjacents areas
		std::vector<AREA> adjAreas = Board::GetAdjacentAreas(_raidArea);
		if (!Board::IsAreaASea(_raidArea))
		{
			std::vector<AREA> terrAreas;
			for (it = adjAreas.begin(); it != adjAreas.end(); it++)
			{
				if (!Board::IsAreaASea(*it) && !Board::IsAreaAPort(*it))
					terrAreas.push_back(*it);
			}
			adjAreas = terrAreas;
		}
			
		std::vector<AREA> raidableAreas;
		for (it = adjAreas.begin(); it != adjAreas.end(); it++)
		{
			BoardPiece* pBoardPiece = pBoard->GetElementAt(ORDERTYPE, *it);
			if (pBoardPiece && _pCurrentPlayer != pBoardPiece->GetOwner())
			{
				ORDER adjOrder = (ORDER)pBoardPiece->GetSubType();
				if (adjOrder == SUPPORT_1 || adjOrder == SUPPORT_2 || adjOrder == SUPPORT_STAR ||
					adjOrder == CONSOLIDATE_1 || adjOrder == CONSOLIDATE_2 || adjOrder == CONSOLIDATE_STAR ||
					adjOrder == RAID_1 || adjOrder == RAID_2 || adjOrder == RAID_STAR)
				{
					raidableAreas.push_back(*it);
				}
				else if (raidType == RAID_STAR && adjOrder == DEFENSE_1 || adjOrder == DEFENSE_2 ||
					adjOrder == DEFENSE_STAR)
				{
					raidableAreas.push_back(*it);
				}					
			}
		}
				
		raidableAreas.push_back(_raidArea);
		_pSelection->Clean();
		CHK_SUCCESS(_pSelection->Init(raidableAreas));

		(_pGame->GetEngine())->RegisterPromptWindow(_pCancelOrderPrompt);
	}

	return L_S_OK;
}
