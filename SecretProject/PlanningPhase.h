#pragma once

#include "GameState.h"

class Game;

class PlanningPhase :
	public GameState
{
public:
	PlanningPhase(Game* ipGame);
	~PlanningPhase();

	virtual L_HRESULT Init();

	virtual L_HRESULT Activate();
	virtual L_HRESULT Deactivate();

private:
	virtual GameState* _GetNextState();

	GameState* _pAssignOrdersState;
	GameState* _pRevealOrdersState;
	GameState* _pRavenState;
};

