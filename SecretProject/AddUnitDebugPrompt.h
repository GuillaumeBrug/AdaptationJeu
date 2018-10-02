#pragma once

#include "WindowPrompt.h"
#include <vector>

class Player;
class Button;

class AddUnitDebugPrompt :
	public WindowPrompt
{
public:
	AddUnitDebugPrompt(int iWinWidth, int iWinHeight);
	~AddUnitDebugPrompt();

	void SetPlayer(int iNbPlayers, Player* ipPlayers[6]);

protected:
	virtual L_HRESULT _Init();

	virtual L_HRESULT _OnElementClicked(int iElementID);

private:
	L_HRESULT _Apply();
	L_HRESULT _UpdateUnitsForCurrentAreaAndPlayer();

	int _NbPlayers;
	Player* _pPlayers[6];
	Player* _pSelectedPlayer;
	AREA _Area;

	int _NbFoot;
	int _NbKnight;
	int _NbEngine;
	int _NbShip;

	std::vector<Button*> _Buttons;
};

