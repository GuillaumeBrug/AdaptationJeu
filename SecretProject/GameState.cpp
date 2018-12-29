#include "GameState.h"
#include "Game.h"
#include "Board.h"
#include "BoardPiece.h"

GameState::GameState(Game* ipGame):_Activated(false), _Completed(false),
_pGame(ipGame), _pCurrentState(NULL), _pCurrentPlayer(NULL)
{
}

GameState::~GameState()
{
	_pGame = NULL;
	_pCurrentState = NULL;
	_pCurrentPlayer = NULL;
}

void GameState::Reinit()
{
	_Activated = false;
	_Completed = false;
}

L_HRESULT GameState::Execute()
{
	CHK_AND_RET_HR(_pCurrentState);

	if (!_pCurrentState->IsActivated() && !_pCurrentState->IsCompleted())
	{
		CHK_SUCCESS(_pCurrentState->Activate());
	}
	else if (_pCurrentState->IsActivated() && !_pCurrentState->IsCompleted())
	{
		CHK_SUCCESS(_pCurrentState->Execute());
	}
	else if (_pCurrentState->IsCompleted())
	{
		_pCurrentState->Deactivate();
		_pCurrentState = _GetNextState();
	}
}

GameState* GameState::_GetNextState() 
{
	return NULL;
}

L_HRESULT GameState::_RemoveOrderFromArea(AREA iArea)
{
	Board* pBoard = _pGame->GetBoard();
	CHK_AND_RET_HR(pBoard);
	BoardPiece* orderPiece = pBoard->GetElementAt(ORDERTYPE, iArea);
	CHK_AND_RET_HR(orderPiece);
	ORDER orderType = (ORDER)orderPiece->GetSubType();

	Player* pPlayer = orderPiece->GetOwner();
	CHK_AND_RET_HR(pPlayer);
	CHK_SUCCESS(pPlayer->RemoveOrderInArea(orderType, iArea));

	return L_S_OK;
}
