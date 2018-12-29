#pragma once

#include "WindowPrompt.h"

class Button;
class Engine;

class AddOrderDebugPrompt :
	public WindowPrompt
{
public:
	AddOrderDebugPrompt(int iWinWidth, int iWinHeight);
	~AddOrderDebugPrompt();

	void SetPlayer(int iNbPlayers, Player* ipPlayers[6]);

	void SetPrompt(WindowPrompt* ipPrompt) { _pPrompt = ipPrompt; }
	void SetEngine(Engine* ipEngine) { _pEngine = ipEngine; }

protected:
	virtual L_HRESULT _Init();

	virtual L_HRESULT _OnElementClicked(int iElementID);

private:
	L_HRESULT _Apply();

	int _NbPlayers;
	Player* _pPlayers[6];
	Player* _pSelectedPlayer;
	AREA _Area;
	ORDER _Order;

	std::vector<Button*> _Buttons;

	WindowPrompt* _pPrompt;
	Engine* _pEngine;
};

