#pragma once

#include "GameState.h"

class Player;
class ChoicePrompt;
class WildCardPrompt;
class SelectionPrompt;
class AssignOrderPrompt;

class RavenChoiceState :
	public GameState
{
public:
	RavenChoiceState(Game* ipGame);
	~RavenChoiceState();

	virtual L_HRESULT Init();

	virtual L_HRESULT Activate();
	virtual L_HRESULT Deactivate();

	virtual L_HRESULT Execute();

private:
	ChoicePrompt* _pChoice;
	WildCardPrompt* _pWildCardPrompt;
	SelectionPrompt* _pSelection;
	AssignOrderPrompt* _pAssignPrompt;
};

