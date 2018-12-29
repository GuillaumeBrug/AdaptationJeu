#pragma once

#include "WindowPrompt.h"

class DefineMovementPrompt :
	public WindowPrompt
{
public:
	DefineMovementPrompt(int iWinWidth, int iWinHeight);
	~DefineMovementPrompt();

	void SetPlayer(Player* ipPlayer) { _pPlayer = ipPlayer; }
	void SetFromArea(AREA iArea) { _FromArea = iArea; }
	void SetToArea(AREA iArea) { _ToArea = iArea; _Initialized = false; }

	void SetUnitsInMove(UNIT iUnit, int iNb);

protected:
	L_HRESULT _Init();

	L_HRESULT _OnElementClicked(int iElementID);

private:
	Player* _pPlayer;
	AREA _FromArea;
	AREA _ToArea;

	std::map<UNIT, int> _unitsInMove;
};

