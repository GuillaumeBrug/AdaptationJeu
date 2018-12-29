#include "PlanningPhase.h"
#include "AssignOrdersState.h"
#include "RevealOrdersState.h"
#include "RavenChoiceState.h"
#include "Game.h"
#include "Player.h"

PlanningPhase::PlanningPhase(Game* ipGame):GameState(ipGame), _pAssignOrdersState(NULL),
_pRevealOrdersState(NULL), _pRavenState(NULL)
{
}

PlanningPhase::~PlanningPhase()
{
	if (NULL != _pAssignOrdersState) delete _pAssignOrdersState; _pAssignOrdersState = NULL;
	if (NULL != _pRevealOrdersState) delete _pRevealOrdersState; _pRevealOrdersState = NULL;
	if (NULL != _pRavenState) delete _pRavenState; _pRavenState = NULL;
}

L_HRESULT PlanningPhase::Init()
{
	_pAssignOrdersState = new AssignOrdersState(_pGame);
	CHK_AND_RET_HR(_pAssignOrdersState);
	CHK_SUCCESS(_pAssignOrdersState->Init());

	_pRevealOrdersState = new RevealOrdersState(_pGame);
	CHK_AND_RET_HR(_pRevealOrdersState);
	CHK_SUCCESS(_pRevealOrdersState->Init());

	_pRavenState = new RavenChoiceState(_pGame);
	CHK_AND_RET_HR(_pRavenState);
	CHK_SUCCESS(_pRavenState->Init());

	return L_S_OK;
}

L_HRESULT PlanningPhase::Activate()
{
	_pGame->SetFirstAsCurrentPlayer();
	_pCurrentState = _pAssignOrdersState;

	_Activated = true;
	return L_S_OK;
}

L_HRESULT PlanningPhase::Deactivate()
{
	_Activated = false;
	return L_S_OK;
}

GameState* PlanningPhase::_GetNextState()
{
	if (_pCurrentState == _pAssignOrdersState)
	{
		_pGame->NextPlayer();
		if (1 == (_pGame->GetCurrentPlayer())->GetThronePosition())
			return _pRevealOrdersState;
		else
			return _pAssignOrdersState;
	}
	else if (_pCurrentState == _pRevealOrdersState)
	{
		return _pRavenState;
	}
	else if (_pCurrentState == _pRavenState)
	{
		_Completed = true;
	}
	
	return NULL;
}
