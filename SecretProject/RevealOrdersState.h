#pragma once
#include "GameState.h"
class RevealOrdersState :
	public GameState
{
public:
	RevealOrdersState(Game* ipGame);
	~RevealOrdersState();

	virtual L_HRESULT Init();

	virtual L_HRESULT Activate();
	virtual L_HRESULT Deactivate();

	virtual L_HRESULT Execute();
};

