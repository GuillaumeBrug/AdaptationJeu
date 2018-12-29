#pragma once

#include "GameState.h"

class Game;
class PlayRaidState;
class PlayMarchState;

class ActionPhase :
	public GameState
{
public:
	ActionPhase(Game* ipGame);
	~ActionPhase();

	virtual L_HRESULT Init();

	virtual L_HRESULT Activate();
	virtual L_HRESULT Deactivate();

private:
	virtual GameState* _GetNextState();

	PlayRaidState* _pRaidState;
	PlayMarchState* _pMarchState;
};

