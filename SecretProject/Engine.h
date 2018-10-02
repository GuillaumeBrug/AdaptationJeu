#pragma once

#include <string>
#include "Tdf_Defs.h"
#include "Player.h"
#include "SDL.h"
#include "SDL_TTF.h"

class Game;
class Board;
class WindowPrompt;

class Engine
{
public:
	Engine();
	~Engine();

	L_HRESULT AddNewPlayer(std::string iName);

	L_HRESULT Init();

	L_HRESULT ProcessEvent(SDL_Event* ipEvent);

	L_HRESULT MoveOn();

	L_HRESULT Render();

	L_HRESULT Clean();

	L_HRESULT RegisterPromptWindow(WindowPrompt* ipPrompt);

private:
	int _NbPlayers;
	Player* _pPlayers[6];
	Game* _pGame;
	Board* _pBoard;
	WindowPrompt* _pPrompt;

	bool _CtrlKeyDown;
	double _ZoomRatio;
	double _MinZoomRatio;
	SDL_Rect _Camera;
	SDL_Rect _BoardSize;
	SDL_Window* _pMainWindow;

	friend class Tdf_Debug;
};

