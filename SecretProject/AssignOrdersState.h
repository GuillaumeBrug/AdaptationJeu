#pragma once

#include "GameState.h"

class Game;
class SelectionPrompt;
class AssignOrderPrompt;
class ValidationPrompt;
class ChoicePrompt;

class AssignOrdersState :
	public GameState
{
public:
	AssignOrdersState(Game* ipGame);
	~AssignOrdersState();

	virtual L_HRESULT Init();

	virtual L_HRESULT Activate();
	virtual L_HRESULT Deactivate();

	virtual L_HRESULT Execute();

private:
	SelectionPrompt* _pSelection;
	AssignOrderPrompt* _pAssignPrompt;
	ValidationPrompt* _pValidationPrompt;
	ChoicePrompt* _pTooStarsPrompt;

	bool _AreaSelected;
};

