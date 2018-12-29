#include "Engine.h"
#include "Game.h"
#include "Board.h"
#include "GraphicElement.h"
#include "WindowPrompt.h"
#include "SelectionPrompt.h"
#include "Tdf_Debug.h"
#include "SDL_syswm.h"
#include "resource.h"
#include <windows.h>
#include <winuser.h>
#include <commctrl.h>

static int _CameraMove = 100;
static Engine* _ThisEngine;

Engine::Engine():_NbPlayers(0), _pGame(NULL), _pBoard(NULL), _pMainWindow(NULL), _ZoomRatio(1.0),
_CtrlKeyDown(false), _pPrompt(NULL), _pSelection(NULL)
{
	_ThisEngine = this;
}

Engine::~Engine()
{
	Clean();
}

L_HRESULT Engine::AddNewPlayer(std::string iName)
{
	if (_NbPlayers >= 6)
		return L_E_FAIL;

	_pPlayers[_NbPlayers] = new Player(iName);
	_NbPlayers++;

	return L_S_OK;
}

LRESULT CALLBACK _MenuProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	Tdf_Debug debug(_ThisEngine);

	switch (uMsg)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_DEBUG_ADDUNITINAREA:
			debug.AddUnitInArea();
			break;
		case ID_DEBUG_ADDORDERINAREA:
			debug.AddOrderInArea();
			break;
		case ID_DEBUG_ADJACENTAREAS:
			debug.AdjacentAreas();
			break;
		}
		break;
	}
	return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}

L_HRESULT Engine::Init()
{
	if (_NbPlayers < 3 || _NbPlayers > 6)
		return L_E_FAIL;

	// Load the images for the Graphic Elements
	CHK_SUCCESS(BoardPiece::LoadMedias());

	_pGame = new Game(_NbPlayers, _pPlayers);
	CHK_AND_RET_HR(_pGame);

	_pBoard = new Board(_NbPlayers, _pPlayers);
	CHK_AND_RET_HR(_pBoard);

	_pMainWindow = SDL_CreateWindow("Trone de Fer - 2nd Edition", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0,
		SDL_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED);

	// Set Borad to the Players
	for (int i = 0; i < _NbPlayers; i++)
	{
		_pPlayers[i]->SetBoard(_pBoard);
	}

	// Initialize the Game
	CHK_SUCCESS(_pGame->Init(_pBoard, this));

	// Initialize the Board
	CHK_SUCCESS(_pBoard->Init());
	
	// Put a menu in the Window
	HWND myWindow;
	HMENU myMenu;

	SDL_SysWMinfo windowinfo;
	SDL_VERSION(&windowinfo.version);
	if (SDL_FALSE == SDL_GetWindowWMInfo(_pMainWindow, &windowinfo))
		return L_E_FAIL;

	myWindow = windowinfo.info.win.window;
	SetWindowSubclass(myWindow, &_MenuProc, 1, 0);
	myMenu = LoadMenu(NULL, MAKEINTRESOURCE(IDR_MENU1));
	SetMenu(myWindow, myMenu);

	SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);

	// Ask for a first render to the Board to initialize the ZoomRatio so all the board width fit in the window
	SDL_Surface* pBoardSurface = NULL;
	CHK_SUCCESS(_pBoard->Render(pBoardSurface));
	CHK_AND_RET_HR(pBoardSurface);

	SDL_Rect boardRect = pBoardSurface->clip_rect;
	SDL_Surface* pWindowSurface = SDL_GetWindowSurface(_pMainWindow);
	CHK_AND_RET_HR(pWindowSurface);
	SDL_Rect windowRect = pWindowSurface->clip_rect;

	// Init ZoomRatio
	_ZoomRatio = (double)windowRect.w / (double)boardRect.w;

	// Calculate the minimum of the Zoom Ratio, ie the Board height is equal to the window height
	_MinZoomRatio = (double)windowRect.h / (double)boardRect.h;

	// Init Camera
	_Camera = windowRect;

	return L_S_OK;
}

L_HRESULT Engine::ProcessEvent(SDL_Event* ipEvent)
{
	CHK_AND_RET_HR(ipEvent);

	if (ipEvent->type == SDL_KEYUP)
	{
		switch (ipEvent->key.keysym.sym)
		{
		case SDLK_LCTRL:
		case SDLK_RCTRL:
			_CtrlKeyDown = false; // Ctrl key is released
			break;
		default:
			break;
		}
	}
	else if (ipEvent->type == SDL_KEYDOWN)
	{
		switch (ipEvent->key.keysym.sym)
		{
		case SDLK_UP:
			if (!_CtrlKeyDown && _Camera.y > _BoardSize.y)
			{
				// Move the Camera up
				if (_Camera.y - _CameraMove >= 0)
					_Camera.y -= _CameraMove; 
				else
					_Camera.y = 0;
			}

			if (_CtrlKeyDown)
				_ZoomRatio += .03; // Zoom
			break;
		case SDLK_DOWN:
			if (!_CtrlKeyDown && _Camera.y + _Camera.h < _BoardSize.y + _BoardSize.h)
			{
				// Move the Camera down
				if (_Camera.y + _CameraMove <= _BoardSize.y + _BoardSize.h)
					_Camera.y += _CameraMove;
				else
					_Camera.y = _BoardSize.y + _BoardSize.h - _Camera.y;
			}
				

			if (_CtrlKeyDown && _ZoomRatio > _MinZoomRatio)
				_ZoomRatio -= .03; // Unzoom
			break;
		case SDLK_LEFT:
			if (_Camera.x > _BoardSize.x)
			{
				// Move the Camera left
				if (_Camera.x - _CameraMove >= 0)
					_Camera.x -= _CameraMove;
				else
					_Camera.x = 0;
			}
				
			break;
		case SDLK_RIGHT:
			if (_Camera.x + _Camera.w < _BoardSize.x + _BoardSize.w)
			{
				// Move the Camera right
				if (_Camera.x + _Camera.w + _CameraMove <= _BoardSize.x + _BoardSize.w)
					_Camera.x += _CameraMove;
				else
					_Camera.x = _BoardSize.x + _BoardSize.w - _Camera.w;
			}
				
			break;
		case SDLK_LCTRL:
		case SDLK_RCTRL:
			_CtrlKeyDown = true; // Ctrl key is pressed
			break;
		case SDLK_u:
			if (_CtrlKeyDown)
			{
				Tdf_Debug debug(this);
				debug.AddUnitInArea();
			}
		default:
			break;
		}
	}
	else if (ipEvent->type == SDL_MOUSEBUTTONDOWN)
	{
		if (ipEvent->button.button == SDL_BUTTON_RIGHT)
		{
			// Display Tooltip if an element is under the click
		}
		else if (ipEvent->button.button == SDL_BUTTON_LEFT)
		{
			if (NULL != _pPrompt)
			{
				SDL_Rect promptPosition = _pPrompt->GetPosition();
				if (ipEvent->button.x >= promptPosition.x && ipEvent->button.x <= promptPosition.x + promptPosition.w &&
					ipEvent->button.y >= promptPosition.y && ipEvent->button.y <= promptPosition.y + promptPosition.h)
				{
					int iX = ipEvent->button.x - promptPosition.x;
					int iY = ipEvent->button.y - promptPosition.y;
					CHK_SUCCESS(_pPrompt->InputClick(iX, iY));
				}				
			}

			if (NULL != _pSelection)
			{
				int iX = (_Camera.x + ipEvent->button.x) / _ZoomRatio;
				int iY = (_Camera.y + ipEvent->button.y) / _ZoomRatio;
				_pSelection->InputClick(iX, iY);
			}
		}
	}

	return L_S_OK;
}

L_HRESULT Engine::MoveOn()
{
	CHK_SUCCESS(_pGame->MoveOn());
	return L_S_OK;
}

L_HRESULT Engine::Render()
{
	SDL_Surface* pBoardSurface = NULL;
	// Get the Board display from the Board
	CHK_SUCCESS(_pBoard->Render(pBoardSurface));
	CHK_AND_RET_HR(pBoardSurface);

	// Modify the Board display according to the Zoom Ratio
	double zoom = (_ZoomRatio > _MinZoomRatio) ? _ZoomRatio : _MinZoomRatio;
	int ratioWidth = zoom * pBoardSurface->clip_rect.w;
	int ratioHeight = zoom * pBoardSurface->clip_rect.h;
	SDL_Surface* pScaledBoardSurface = SDL_CreateRGBSurface(0, ratioWidth, ratioHeight, 32, 0, 0, 0, 0);
	SDL_BlitScaled(pBoardSurface, NULL, pScaledBoardSurface, NULL);

	// Update the size of the Board
	_BoardSize = pScaledBoardSurface->clip_rect;

	// Recenter the Camera after Zoom to avoid displaying the white background if not needed
	int diff = _Camera.x + _Camera.w - _BoardSize.w;
	if (diff > 0)
		_Camera.x -= diff;
	diff = _Camera.y + _Camera.h - _BoardSize.h;
	if (diff > 0)
		_Camera.y -= diff;

	// Clean the Board display; dont needed anymore
	SDL_FreeSurface(pBoardSurface);

	// Get the Surface of the Window
	SDL_Surface* pWindowSurface = SDL_GetWindowSurface(_pMainWindow);
	CHK_AND_RET_HR(pWindowSurface);
	// Init Window surface with a White screen
	SDL_FillRect(pWindowSurface, NULL, SDL_MapRGB(pWindowSurface->format, 255, 255, 255));
	
	SDL_Rect boardShift = pWindowSurface->clip_rect;
	if (ratioWidth < boardShift.w)
	{
		// Board display width is smaller than the Window width, we center the Board display
		boardShift.x = (boardShift.w - ratioWidth) / 2;
		_Camera.x = 0;
	}

	// Put the Board display in the Window's surface
	SDL_BlitSurface(pScaledBoardSurface, &_Camera, pWindowSurface, &boardShift);

	// Clean the Scaled Board display; dont needed anymore
	SDL_FreeSurface(pScaledBoardSurface);

	// If a Window is prompted, render it
	if (_pPrompt)
	{
		if (_pPrompt->IsComplete() && _pPrompt->DoDelete())
		{
			delete _pPrompt;
			_pPrompt = NULL;
		}
		else if (_pPrompt->IsComplete())
		{
			_pPrompt = NULL;
		}
		else if(!_pPrompt->IsComplete())
		{
			SDL_Surface* pPromptSurface = NULL;
			SDL_Rect promptPosition;
			_pPrompt->Render(pPromptSurface, promptPosition);
			CHK_AND_RET_HR(pPromptSurface);

			SDL_BlitSurface(pPromptSurface, NULL, pWindowSurface, &promptPosition);
		}
	}

	//Update the surface 
	SDL_UpdateWindowSurface(_pMainWindow);

	return L_S_OK;
}

L_HRESULT Engine::Clean()
{
	delete _pGame; _pGame = NULL;
	delete _pBoard; _pBoard = NULL;

	for (int i = 0; i < _NbPlayers; i++)
		delete _pPlayers[i];
	_NbPlayers = 0;

	_pPrompt = NULL;
	_pSelection = NULL;

	SDL_DestroyWindow(_pMainWindow);

	BoardPiece::UnloadMedias();

	return L_S_OK;
}

L_HRESULT Engine::RegisterPromptWindow(WindowPrompt* ipPrompt)
{
	if (NULL != _pPrompt)
		return L_E_FAIL;

	_pPrompt = ipPrompt;

	return L_S_OK;
}

L_HRESULT Engine::RegisterSelectionPrompt(SelectionPrompt* ipSelection)
{
	if (NULL != _pSelection)
		return L_E_FAIL;

	_pSelection = ipSelection;

	return L_S_OK;
}

L_HRESULT Engine::GetWindowDimension(int& oWidth, int& oHeight)
{
	CHK_AND_RET_HR(_pMainWindow);

	SDL_GetWindowSize(_pMainWindow, &oWidth, &oHeight);
	
	return L_S_OK;
}