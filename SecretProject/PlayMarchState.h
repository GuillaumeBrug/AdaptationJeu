#pragma once

#include "GameState.h"

class ValidationPrompt;
class SelectionPrompt;
class DefineMovementPrompt;

class PlayMarchState :
	public GameState
{
public:
	PlayMarchState(Game* ipGame);
	~PlayMarchState();

	virtual L_HRESULT Init();

	virtual L_HRESULT Activate();
	virtual L_HRESULT Deactivate();

	virtual L_HRESULT Execute();

private:
	ValidationPrompt* _pCancelOrderPrompt;
	SelectionPrompt* _pSelectionOrder;
	SelectionPrompt* _pSelectionUnit;

	DefineMovementPrompt* _pMovementPrompt;
	
	AREA _marchArea;
	AREA _toArea;
	bool  _selectionUnitPrompted;
};

