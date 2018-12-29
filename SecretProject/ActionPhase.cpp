#include "ActionPhase.h"
#include "PlayRaidState.h"
#include "PlayMarchState.h"
#include "Game.h"
#include "Player.h"

ActionPhase::ActionPhase(Game* ipGame):GameState(ipGame), _pRaidState(NULL), _pMarchState(NULL)
{
}

ActionPhase::~ActionPhase()
{
	if (NULL != _pRaidState)
		delete _pRaidState;
	_pRaidState = NULL;

	if (NULL != _pMarchState)
		delete _pMarchState;
	_pMarchState = NULL;
}

L_HRESULT ActionPhase::Init()
{
	_pRaidState = new PlayRaidState(_pGame);
	CHK_AND_RET_HR(_pRaidState);
	CHK_SUCCESS(_pRaidState->Init());

	_pMarchState = new PlayMarchState(_pGame);
	CHK_AND_RET_HR(_pMarchState);
	CHK_SUCCESS(_pMarchState->Init());

	return L_S_OK;
}

L_HRESULT ActionPhase::Activate()
{
	_pGame->SetFirstAsCurrentPlayer();

	Player* player = _pGame->GetCurrentPlayer();
	CHK_AND_RET_HR(player);
	int thronePos = player->GetThronePosition();
	
	if (player->HasRaidOrderToPlay())
		_pCurrentState = _pRaidState;
	else
	{
		bool noRaidOrdersFound = false;
		while (!player->HasRaidOrderToPlay())
		{
			player = _pGame->NextPlayer();
			CHK_AND_RET_HR(player);

			if (thronePos == player->GetThronePosition())
			{
				noRaidOrdersFound = true;
				break;
			}
		}

		if (noRaidOrdersFound)
		{
			if (player->HasMarchOrderToPlay())
				_pCurrentState = _pMarchState;
			else
			{
				bool noMarchOrdersFound = false;
				while (!player->HasMarchOrderToPlay())
				{
					player = _pGame->NextPlayer();
					CHK_AND_RET_HR(player);

					if (thronePos == player->GetThronePosition())
					{
						noMarchOrdersFound = true;
						break;
					}
				}

				if (noMarchOrdersFound)
					int i = 0;
				else
					_pCurrentState = _pMarchState;
			}
		}
		else
			_pCurrentState = _pRaidState;
	}

	_Activated = true;
	return L_S_OK;
}

L_HRESULT ActionPhase::Deactivate()
{
	_Activated = false;
	_Completed = false;
	return L_S_OK;
}

GameState* ActionPhase::_GetNextState()
{
	Player* player = _pGame->GetCurrentPlayer();
	if (NULL == player) return NULL;
	int thronePos = player->GetThronePosition();

	if (_pCurrentState == _pRaidState)
	{
		bool noRaidOrdersFound = false;
		do
		{
			player = _pGame->NextPlayer();
			if (NULL == player) return NULL;

			if (thronePos == player->GetThronePosition())
			{
				noRaidOrdersFound = true;
				break;
			}
		} while (!player->HasRaidOrderToPlay());

		if (noRaidOrdersFound)
			return _pMarchState;
		else
		{
			_pRaidState->Reinit();
			return _pRaidState;
		}
	}
	else if (_pCurrentState == _pMarchState)
	{
		bool noMarchOrdersFound = false;
		do
		{
			player = _pGame->NextPlayer();
			if (NULL == player) return NULL;

			if (thronePos == player->GetThronePosition())
			{
				noMarchOrdersFound = true;
				break;
			}
		} while (!player->HasMarchOrderToPlay());

		if (noMarchOrdersFound)
			return NULL;
		else
		{
			_pMarchState->Reinit();
			return _pMarchState;
		}
	}


	return NULL;
}
