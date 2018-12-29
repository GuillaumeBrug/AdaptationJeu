#pragma once

#include "WindowPrompt.h"

class Game;

class AssignOrderPrompt :
	public WindowPrompt
{
public:
	AssignOrderPrompt(int iWidth, int iHeight);
	~AssignOrderPrompt();

	void SetGame(Game* ipGame) { _pGame = ipGame; }
	void SetPlayer(Player* ipPlayer) { _pPlayer = ipPlayer; }
	void SetArea(AREA iArea) { _Area = iArea; }
	AREA GetArea() { return _Area; }

	ORDER GetSelectedOrder() { return _SelectedOrder; }

	virtual void Reset();

protected:
	L_HRESULT _Init();

	L_HRESULT _OnElementClicked(int iElementID);

private:
	Game* _pGame;
	Player* _pPlayer;
	AREA _Area;
	ORDER _SelectedOrder;
};

