#include "Game.h"
#include "Player.h"
#include <vector>
#include <algorithm>
#include <ctime>

Game::Game(int iNbPlayers, Player* ipPlayers[6]):_NbPlayers(iNbPlayers), _WildlingForce(0)
{
	for(int i = 0; i < _NbPlayers; i++)
		_pPlayers[i] = ipPlayers[i];
}

Game::~Game()
{
}

L_HRESULT Game::Init()
{
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

	return L_S_OK;
}
