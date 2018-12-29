#include "AssignOrdersState.h"
#include "SelectionPrompt.h"
#include "Game.h"
#include "Player.h"
#include "Engine.h"
#include "AssignOrderPrompt.h"
#include "ValidationPrompt.h"
#include "ChoicePrompt.h"

AssignOrdersState::AssignOrdersState(Game* ipGame) :GameState(ipGame), _pSelection(NULL), _pAssignPrompt(NULL),
_AreaSelected(false), _pValidationPrompt(NULL), _pTooStarsPrompt(NULL)
{
}

AssignOrdersState::~AssignOrdersState()
{
	if (NULL != _pSelection)
		delete _pSelection;
	_pSelection = NULL;

	if (NULL != _pAssignPrompt)
		delete _pAssignPrompt;
	_pAssignPrompt = NULL;

	if(NULL != _pValidationPrompt)
		delete _pValidationPrompt;
	_pValidationPrompt = NULL;

	if (NULL != _pTooStarsPrompt)
		delete _pTooStarsPrompt;
	_pTooStarsPrompt = NULL;
}

L_HRESULT AssignOrdersState::Init()
{
	int iWidth = 0, iHeight = 0;
	(_pGame->GetEngine())->GetWindowDimension(iWidth, iHeight);
	_pAssignPrompt = new AssignOrderPrompt(iWidth, iHeight);
	CHK_AND_RET_HR(_pAssignPrompt);

	_pValidationPrompt = new ValidationPrompt(iWidth, iHeight, "Fin de la phase de programmation ?");
	CHK_AND_RET_HR(_pValidationPrompt);

	_pTooStarsPrompt = new ChoicePrompt(iWidth, iHeight);
	CHK_AND_RET_HR(_pTooStarsPrompt);
	std::vector<std::pair<int, std::string>> choices;
	choices.push_back({ 0, "OK" });
	_pTooStarsPrompt->SetChoices(choices);
	_pTooStarsPrompt->SetText("Trop d'ordres spéciaux ont été joué !");

	return L_S_OK;
}

L_HRESULT AssignOrdersState::Activate()
{
	_pCurrentPlayer = _pGame->GetCurrentPlayer();
	CHK_AND_RET_HR(_pCurrentPlayer);

	_pSelection = new SelectionPrompt(SELECTORDER, _pGame->GetBoard(), _pCurrentPlayer);
	CHK_AND_RET_HR(_pSelection);

	CHK_SUCCESS(_pSelection->Init(_pCurrentPlayer->GetAreasWithUnits()));
	(_pGame->GetEngine())->RegisterSelectionPrompt(_pSelection);

	_pAssignPrompt->SetGame(_pGame);
	_pAssignPrompt->SetPlayer(_pCurrentPlayer);

	(_pGame->GetEngine())->RegisterPromptWindow(_pValidationPrompt);

	_Activated = true;

	return L_S_OK;
}

L_HRESULT AssignOrdersState::Deactivate()
{
	CHK_AND_RET_HR(_pSelection);
	_pSelection->Clean();
	delete _pSelection;
	_pSelection = NULL;
	(_pGame->GetEngine())->UnregisterSelectionPrompt();
	
	(_pGame->GetEngine())->UnregisterPromptWindow();

	_AreaSelected = false;
	_Activated = false;
	_Completed = false;

	return L_S_OK;
}

L_HRESULT AssignOrdersState::Execute()
{
	CHK_AND_RET_HR(_pSelection);
	CHK_AND_RET_HR(_pAssignPrompt);
	CHK_AND_RET_HR(_pCurrentPlayer);

	AREA area = _pSelection->GetSelectedArea();
	if (UNDEFINED_AREA != area && !_AreaSelected)
	{
		(_pGame->GetEngine())->UnregisterPromptWindow();

		_AreaSelected = true;
		_pAssignPrompt->SetArea(area);
		(_pGame->GetEngine())->RegisterPromptWindow(_pAssignPrompt);
		
		(_pGame->GetEngine())->UnregisterSelectionPrompt();
		_pSelection->Clean();
	}

	if (_pAssignPrompt->IsComplete())
	{
		ORDER order = _pAssignPrompt->GetSelectedOrder();
		AREA area = _pAssignPrompt->GetArea();
		if (UNDEFINED_ORDER != order && UNDEFINED_AREA != area)
			CHK_SUCCESS(_pCurrentPlayer->AddOrderInArea(order, area));

		(_pGame->GetEngine())->UnregisterPromptWindow();
		delete _pAssignPrompt;

		int iWidth = 0, iHeight = 0;
		(_pGame->GetEngine())->GetWindowDimension(iWidth, iHeight);
		_pAssignPrompt = new AssignOrderPrompt(iWidth, iHeight);
		CHK_AND_RET_HR(_pAssignPrompt);
		_pAssignPrompt->SetGame(_pGame);
				
		CHK_SUCCESS(_pSelection->Init(_pCurrentPlayer->GetAreasWithUnits()));
		(_pGame->GetEngine())->RegisterSelectionPrompt(_pSelection);
		_AreaSelected = false;

		_pAssignPrompt->SetPlayer(_pCurrentPlayer);

		(_pGame->GetEngine())->RegisterPromptWindow(_pValidationPrompt);
	}

	if (_pValidationPrompt->IsComplete())
	{
		int nbStarsAllowed = _pGame->GetNbStarsAllowed(_pCurrentPlayer);

		int nbStarsPlanned = 0;
		std::vector<ORDER> orders = (_pCurrentPlayer->GetPlannedOrders());
		std::vector<ORDER>::iterator it;
		for (it = orders.begin(); it != orders.end(); it++)
		{
			switch (*it)
			{
			case SUPPORT_STAR:
			case MARCH_STAR:
			case DEFENSE_STAR:
			case CONSOLIDATE_STAR:
			case RAID_STAR:
				nbStarsPlanned++;
			}
		}

		(_pGame->GetEngine())->UnregisterPromptWindow();
		_pValidationPrompt->Reset();

		if (nbStarsAllowed >= nbStarsPlanned)
			_Completed = true;
		else
			(_pGame->GetEngine())->RegisterPromptWindow(_pTooStarsPrompt);
	}

	if (_pTooStarsPrompt->IsComplete())
	{
		_pTooStarsPrompt->Reset();
		(_pGame->GetEngine())->UnregisterPromptWindow();

		(_pGame->GetEngine())->RegisterPromptWindow(_pValidationPrompt);
	}
		

	return L_S_OK;
}
