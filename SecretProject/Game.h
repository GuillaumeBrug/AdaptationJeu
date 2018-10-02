#pragma once

#include "Tdf_Defs.h"

class Player;

class Game
{
public:
	Game(int iNbPlayers, Player* ipPlayers[6]);
	~Game();

	L_HRESULT Init();

	int GetiWildlingFore() { return _WildlingForce; }

private:
	int _NbPlayers;
	Player* _pPlayers[6];

	int _WildlingForce;
};

