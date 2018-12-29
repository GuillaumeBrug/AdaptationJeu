#pragma once

#include "Tdf_Defs.h"
#include <vector>

class Player;
class GameState;
class Board;
class Engine;

class Game
{
public:
	Game(int iNbPlayers, Player* ipPlayers[6]);
	~Game();

	L_HRESULT Init(Board* ipBoard, Engine* ipEngine);

	L_HRESULT MoveOn();

	int GetiWildlingFore() { return _WildlingForce; }

	Board* GetBoard() { return _pBoard; }
	Engine* GetEngine() { return _pEngine; }

	Player* GetCurrentPlayer() { return _pCurrentPlayer; }
	Player* NextPlayer();
	void SetFirstAsCurrentPlayer();

	Player* GetThroneOwner();
	Player* GetSwordOwner();
	Player* GetRavenOwner();

	std::vector<ORDER> GetAvailableOrder(Player* ipPlayer);
	int GetNbStarsAllowed(Player* ipPlayer);

private:
	int _NbPlayers;
	Player* _pPlayers[6];
	Player* _pCurrentPlayer;
	Board* _pBoard;
	Engine* _pEngine;

	int _WildlingForce;
	int _Turn;
	GameState* _pWesterosPhase;
	GameState* _pPlanningPhase;
	GameState* _pActionPhase;

	GameState* _pCurrentPhase;
};

