#pragma once

#include "GameState.h"

class SelectionPrompt;
class ChoicePrompt;
class ValidationPrompt;

class PlayRaidState :
	public GameState
{
public:
	PlayRaidState(Game* ipGame);
	~PlayRaidState();

	virtual L_HRESULT Init();

	virtual L_HRESULT Activate();
	virtual L_HRESULT Deactivate();

	virtual L_HRESULT Execute();

private:
	SelectionPrompt* _pSelection;
	AREA _raidArea;
	AREA _raidedArea;
	ChoicePrompt* _pChoicePrompt;
	ValidationPrompt* _pCancelOrderPrompt;
};

