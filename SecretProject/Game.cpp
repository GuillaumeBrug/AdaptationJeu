#include "Game.h"
#include "Player.h"
#include "WesterosPhase.h"
#include "PlanningPhase.h"
#include "ActionPhase.h"
#include <vector>
#include <algorithm>
#include <ctime>

Game::Game(int iNbPlayers, Player* ipPlayers[6]):_NbPlayers(iNbPlayers), _WildlingForce(0),
_pWesterosPhase(NULL), _pPlanningPhase(NULL), _pActionPhase(NULL), _pCurrentPhase(NULL),
_Turn(1), _pCurrentPlayer(NULL), _pBoard(NULL), _pEngine(NULL)
{
	for(int i = 0; i < _NbPlayers; i++)
		_pPlayers[i] = ipPlayers[i];
}

Game::~Game()
{
	if (NULL != _pWesterosPhase)
		delete _pWesterosPhase;
	_pWesterosPhase = NULL;

	if (NULL != _pPlanningPhase)
		delete _pPlanningPhase;
	_pPlanningPhase = NULL;

	if (NULL != _pActionPhase)
		delete _pActionPhase;
	_pActionPhase = NULL;

	_pCurrentPhase = NULL;
	_pCurrentPlayer = NULL;
	_pBoard = NULL;
	_pEngine = NULL;
}

L_HRESULT Game::Init(Board* ipBoard, Engine* ipEngine)
{
	CHK_AND_RET_HR(ipBoard);
	_pBoard = ipBoard;

	CHK_AND_RET_HR(ipEngine);
	_pEngine = ipEngine;

	srand(unsigned(time(NULL)));
	std::vector<int>::iterator it;
	std::vector<int> tableau;
	tableau.push_back(1); tableau.push_back(2); tableau.push_back(3);
	if(_NbPlayers > 3)
		tableau.push_back(4);
	if (_NbPlayers > 4)
		tableau.push_back(5);
	if (_NbPlayers > 5)
		tableau.push_back(6);
	random_shuffle(tableau.begin(), tableau.end());

	int* tabShuffled= tableau.data();
	for (int i = 0; i < _NbPlayers; i++)
	{
		_pPlayers[i]->Init((HOUSE)tableau[i]);
	}

	// Readjust the influence track in function of the number of players
	if (_NbPlayers < 6)
	{
		std::vector<Player*> throneTrack(6);
		std::vector<Player*> fiefTrack(6);
		std::vector<Player*> courtTrack(6);
		for (int i = 0; i < _NbPlayers; i++)
		{
			int position = _pPlayers[i]->GetThronePosition();
			throneTrack[position - 1] = _pPlayers[i];

			position = _pPlayers[i]->GetFiefPosition();
			fiefTrack[position - 1] = _pPlayers[i];

			position = _pPlayers[i]->GetCourtPosition();
			courtTrack[position - 1] = _pPlayers[i];
		}

		std::vector<Player*>::iterator it = throneTrack.begin();
		while (it != throneTrack.end())
		{
			if (NULL == *it)
				it = throneTrack.erase(it);
			else
				it++;
		}
		for (it = throneTrack.begin(); it != throneTrack.end(); it++)
		{
			int position = std::distance(throneTrack.begin(), it);
			(*it)->SetThronePosition(position + 1);
		}

		it = fiefTrack.begin();
		while (it != fiefTrack.end())
		{
			if (NULL == *it)
				it = fiefTrack.erase(it);
			else
				it++;
		}
		for (it = fiefTrack.begin(); it != fiefTrack.end(); it++)
		{
			int position = std::distance(fiefTrack.begin(), it);
			(*it)->SetFiefPosition(position + 1);
		}

		it = courtTrack.begin();
		while (it != courtTrack.end())
		{
			if (NULL == *it)
				it = courtTrack.erase(it);
			else
				it++;
		}
		for (it = courtTrack.begin(); it != courtTrack.end(); it++)
		{
			int position = std::distance(courtTrack.begin(), it);
			(*it)->SetCourtPosition(position + 1);
		}
	}

	// Create Game States
	_pWesterosPhase = new WesterosPhase(this);
	CHK_AND_RET_HR(_pWesterosPhase);
	CHK_SUCCESS(_pWesterosPhase->Init());

	_pPlanningPhase = new PlanningPhase(this);
	CHK_AND_RET_HR(_pPlanningPhase);
	CHK_SUCCESS(_pPlanningPhase->Init());
	_pCurrentPhase = _pPlanningPhase;

	_pActionPhase = new ActionPhase(this);
	CHK_AND_RET_HR(_pActionPhase);
	CHK_SUCCESS(_pActionPhase->Init());

	_pCurrentPlayer = _pPlayers[0];

	return L_S_OK;
}

L_HRESULT Game::MoveOn()
{
	if (!_pCurrentPhase->IsActivated() && !_pCurrentPhase->IsCompleted())
	{
		CHK_SUCCESS(_pCurrentPhase->Activate());
	}
	else if (_pCurrentPhase->IsActivated() && !_pCurrentPhase->IsCompleted())
	{
		CHK_SUCCESS(_pCurrentPhase->Execute());
	}
	else if (_pCurrentPhase->IsCompleted())
	{
		_pCurrentPhase->Deactivate();
		if (_pCurrentPhase == _pWesterosPhase)
		{
			_pCurrentPhase = _pPlanningPhase;
		}
		else if (_pCurrentPhase == _pPlanningPhase)
		{
			_pCurrentPhase = _pActionPhase;
		}
		else if (_pCurrentPhase == _pActionPhase)
		{
			_pCurrentPhase = _pWesterosPhase;
			_Turn++;
		}
	}

	return L_S_OK;
}

std::vector<ORDER> Game::GetAvailableOrder(Player* ipPlayer)
{
	std::vector<ORDER> orders;

	orders.push_back(MARCH_MINUS);
	orders.push_back(MARCH);
	orders.push_back(SUPPORT_1);
	orders.push_back(SUPPORT_2);
	orders.push_back(DEFENSE_1);
	orders.push_back(DEFENSE_2);
	orders.push_back(CONSOLIDATE_1);
	orders.push_back(CONSOLIDATE_2);
	orders.push_back(RAID_1);
	orders.push_back(RAID_2);

	int courtPosition = ipPlayer->GetCourtPosition();
	if((_NbPlayers > 4 && courtPosition < 5) || (_NbPlayers <= 4 && courtPosition < 4))
	{
		orders.push_back(SUPPORT_STAR);
		orders.push_back(MARCH_STAR);
		orders.push_back(DEFENSE_STAR);
		orders.push_back(CONSOLIDATE_STAR);
		orders.push_back(RAID_STAR);
	}

	return orders;
}

int Game::GetNbStarsAllowed(Player* ipPlayer)
{
	int courtPosition = ipPlayer->GetCourtPosition();
	if (_NbPlayers > 4) 
	{
		if (courtPosition < 3)
			return 3;
		else if (courtPosition == 3)
			return 2;
		else if (courtPosition == 4)
			return 1;
		else
			return 0;
	}
	else if (_NbPlayers <= 4)
	{
		if (courtPosition == 1)
			return 3;
		else if (courtPosition == 2)
			return 2;
		else if (courtPosition == 3)
			return 1;
		else
			return 0;
	}

	return 0;
}

Player* Game::NextPlayer()
{
	int position = _pCurrentPlayer->GetThronePosition();
	int nextPosition = position == _NbPlayers ? 1 : position + 1;

	for (int i = 0; i < _NbPlayers; i++)
	{
		int pos = _pPlayers[i]->GetThronePosition();
		if (pos == nextPosition)
		{
			_pCurrentPlayer = _pPlayers[i];
			return _pCurrentPlayer;
		}
	}

	return NULL;
}

void Game::SetFirstAsCurrentPlayer()
{
	for (int i = 0; i < _NbPlayers; i++)
	{
		int pos = _pPlayers[i]->GetThronePosition();
		if (1 == pos)
		{
			_pCurrentPlayer = _pPlayers[i];
			break;
		}
	}
}

Player* Game::GetThroneOwner()
{
	for (int i = 0; i < _NbPlayers; i++)
	{
		Player* player = _pPlayers[i];
		if (NULL == player)
			return NULL;

		if (1 == player->GetThronePosition())
			return player;
	}

	return NULL;
}

Player* Game::GetSwordOwner()
{
	for (int i = 0; i < _NbPlayers; i++)
	{
		Player* player = _pPlayers[i];
		if (NULL == player)
			return NULL;

		if (1 == player->GetFiefPosition())
			return player;
	}

	return NULL;
}

Player* Game::GetRavenOwner()
{
	for (int i = 0; i < _NbPlayers; i++)
	{
		Player* player = _pPlayers[i];
		if (NULL == player)
			return NULL;

		if (1 == player->GetCourtPosition())
			return player;
	}

	return NULL;
}
