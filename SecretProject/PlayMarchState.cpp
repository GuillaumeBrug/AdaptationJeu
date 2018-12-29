#include "PlayMarchState.h"
#include "Game.h"
#include "Engine.h"
#include "Board.h"
#include "ValidationPrompt.h"
#include "SelectionPrompt.h"
#include "DefineMovementPrompt.h"

PlayMarchState::PlayMarchState(Game* ipGame):GameState(ipGame), _marchArea(UNDEFINED_AREA), _pCancelOrderPrompt(NULL),
_pSelectionOrder(NULL), _pSelectionUnit(NULL), _selectionUnitPrompted(false), _pMovementPrompt(NULL),
_toArea(UNDEFINED_AREA)
{
}

PlayMarchState::~PlayMarchState()
{
	if (NULL != _pSelectionOrder)
		delete _pSelectionOrder;
	_pSelectionOrder = NULL;

	if (NULL != _pSelectionUnit)
		delete _pSelectionUnit;
	_pSelectionUnit = NULL;

	if (NULL != _pCancelOrderPrompt)
		delete _pCancelOrderPrompt;
	_pCancelOrderPrompt = NULL;

	if (NULL != _pMovementPrompt)
		delete _pMovementPrompt;
	_pMovementPrompt = NULL;
}

L_HRESULT PlayMarchState::Init()
{
	int width = 0, height = 0;
	(_pGame->GetEngine())->GetWindowDimension(width, height);
	_pCancelOrderPrompt = new ValidationPrompt(width, height, "Annuler cet ordre ?");
	CHK_AND_RET_HR(_pCancelOrderPrompt);
	_pCancelOrderPrompt->OverrideButtonText("Annulé");

	_pMovementPrompt = new DefineMovementPrompt(width, height);
	CHK_AND_RET_HR(_pMovementPrompt);

	return L_S_OK;
}

L_HRESULT PlayMarchState::Activate()
{
	_pCurrentPlayer = _pGame->GetCurrentPlayer();
	CHK_AND_RET_HR(_pCurrentPlayer);

	if (NULL == _pSelectionOrder)
		_pSelectionOrder = new SelectionPrompt(SELECTORDER, _pGame->GetBoard(), _pCurrentPlayer);
	CHK_AND_RET_HR(_pSelectionOrder);
	CHK_SUCCESS(_pSelectionOrder->Init(_pCurrentPlayer->GetAreaMarchOrders()));

	(_pGame->GetEngine())->RegisterSelectionPrompt(_pSelectionOrder);

	if (NULL == _pSelectionUnit)
		_pSelectionUnit = new SelectionPrompt(SELECTUNIT, _pGame->GetBoard(), _pCurrentPlayer);
	CHK_AND_RET_HR(_pSelectionUnit);

	_Activated = true;
	return L_S_OK;
}

L_HRESULT PlayMarchState::Deactivate()
{
	_marchArea = UNDEFINED_AREA;
	_Activated = false;
	_Completed = false;
	return L_S_OK;
}

L_HRESULT PlayMarchState::Execute()
{
	CHK_AND_RET_HR(_pCurrentPlayer);

	bool marchSelected = false, toSelected = false;
	CHK_AND_RET_HR(_pSelectionOrder);
	if (_marchArea == UNDEFINED_AREA)
	{
		_marchArea = _pSelectionOrder->GetSelectedArea();
		if(_marchArea != UNDEFINED_AREA)
			marchSelected = true;
	}
	
	CHK_AND_RET_HR(_pSelectionUnit);
	if (_toArea == UNDEFINED_AREA)
	{
		_toArea = _pSelectionUnit->GetSelectedArea();
		if (_toArea != UNDEFINED_AREA)
			toSelected = true;
	}

	if (_pCancelOrderPrompt && _pCancelOrderPrompt->IsComplete())
	{
		_pCancelOrderPrompt->Reset();
		_pSelectionUnit->Clean();
		(_pGame->GetEngine())->UnregisterSelectionPrompt();
		(_pGame->GetEngine())->UnregisterPromptWindow();

		CHK_SUCCESS(_RemoveOrderFromArea(_marchArea));
		_Completed = true;
		return L_S_OK;
	}

	if (marchSelected)
	{
		(_pGame->GetEngine())->RegisterPromptWindow(_pCancelOrderPrompt);

		_pSelectionOrder->Clean();
		(_pGame->GetEngine())->UnregisterSelectionPrompt();

		_pSelectionUnit->Init(Board::GetAdjacentAreas(_marchArea));
		CHK_SUCCESS(_pSelectionUnit->AddSelecter(SELECTORDER, _marchArea));
		(_pGame->GetEngine())->RegisterSelectionPrompt(_pSelectionUnit);

		_pMovementPrompt->SetFromArea(_marchArea);
	}

	if (toSelected)
	{
		(_pGame->GetEngine())->UnregisterPromptWindow();

		_pSelectionUnit->Clean();
		(_pGame->GetEngine())->UnregisterSelectionPrompt();

		if (_toArea == _marchArea)
		{
			_marchArea = UNDEFINED_AREA;
			_toArea = UNDEFINED_AREA;

			CHK_SUCCESS(_pSelectionOrder->Init(_pCurrentPlayer->GetAreaMarchOrders()));
			(_pGame->GetEngine())->RegisterSelectionPrompt(_pSelectionOrder);
		}
		else
		{
			_pMovementPrompt->SetToArea(_toArea);
			(_pGame->GetEngine())->RegisterPromptWindow(_pMovementPrompt);
		}
	}

	if (_pMovementPrompt->IsComplete())
	{
		_pMovementPrompt->Reset();
		(_pGame->GetEngine())->UnregisterPromptWindow();
		_toArea = UNDEFINED_AREA;

		_pSelectionUnit->Init(Board::GetAdjacentAreas(_marchArea));
		CHK_SUCCESS(_pSelectionUnit->AddSelecter(SELECTORDER, _marchArea));
		(_pGame->GetEngine())->RegisterSelectionPrompt(_pSelectionUnit);
	}

	return L_S_OK;
}
