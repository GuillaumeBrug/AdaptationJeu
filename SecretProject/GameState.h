#pragma once

#include "Tdf_Defs.h"
#include <vector>

class Game;
class Player;

class GameState
{
public:
	virtual ~GameState();

	virtual L_HRESULT Init() = 0;
	void Reinit();

	virtual L_HRESULT Activate() = 0;
	virtual L_HRESULT Deactivate() = 0;
	bool IsActivated() { return _Activated; }

	bool IsCompleted() { return _Completed; }

	virtual L_HRESULT Execute();

protected:
	GameState(Game* ipGame);

	virtual GameState* _GetNextState();
	L_HRESULT _RemoveOrderFromArea(AREA iArea);

	Game* _pGame;
	GameState* _pCurrentState;
	Player* _pCurrentPlayer;

	bool _Activated;
	bool _Completed;
};

