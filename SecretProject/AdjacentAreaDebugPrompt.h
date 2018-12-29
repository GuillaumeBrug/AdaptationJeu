#pragma once

#include "WindowPrompt.h"
#include "Game.h"

class SelectionPrompt;

class AdjacentAreaDebugPrompt :
	public WindowPrompt
{
public:
	AdjacentAreaDebugPrompt(int iWinWidth, int iWinHeight);
	~AdjacentAreaDebugPrompt();

	void SetGame(Game* ipGame) { _pGame = ipGame; }

protected:
	virtual L_HRESULT _Init();

	virtual L_HRESULT _OnElementClicked(int iElementID);

private:
	SelectionPrompt* _pSelection;
	AREA _Area;
	Game* _pGame;
};

