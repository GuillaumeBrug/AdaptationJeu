#pragma once

#include "GameState.h"

class Game;

class WesterosPhase :
	public GameState
{
public:
	WesterosPhase(Game* ipGame);
	~WesterosPhase();

	virtual L_HRESULT Init();

	virtual L_HRESULT Activate();
	virtual L_HRESULT Deactivate();

private:
	virtual GameState* _GetNextState();
};

