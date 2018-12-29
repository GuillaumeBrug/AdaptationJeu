#include "Tdf_Debug.h"
#include "Engine.h"
#include "SDL_syswm.h"
#include "resource.h"
#include "AddUnitDebugPrompt.h"
#include "AddOrderDebugPrompt.h"
#include "AdjacentAreaDebugPrompt.h"
#include "SelectionPrompt.h"
#include <windows.h>
#include <winuser.h>

Tdf_Debug::Tdf_Debug(Engine* ipEngine):_pEngine(ipEngine)
{
}

Tdf_Debug::~Tdf_Debug()
{
	_pEngine = NULL;
}

void Tdf_Debug::AddUnitInArea()
{
	if (NULL == _pEngine)
		return;

	int width = 0, height = 0;
	SDL_GetWindowSize(_pEngine->_pMainWindow, &width, &height);

	AddUnitDebugPrompt* pPrompt = new AddUnitDebugPrompt(width, height);
	if (NULL == pPrompt)
		return;

	pPrompt->SetPlayer(_pEngine->_NbPlayers, _pEngine->_pPlayers);

	_pEngine->UnregisterPromptWindow();
	L_HRESULT res = _pEngine->RegisterPromptWindow(pPrompt);
	if (L_E_FAIL == res)
	{
		delete pPrompt;
		pPrompt = NULL;
	}
}

void Tdf_Debug::AddOrderInArea()
{
	if (NULL == _pEngine)
		return;

	int width = 0, height = 0;
	SDL_GetWindowSize(_pEngine->_pMainWindow, &width, &height);

	AddOrderDebugPrompt* pPrompt = new AddOrderDebugPrompt(width, height);
	if (NULL == pPrompt)
		return;

	pPrompt->SetPlayer(_pEngine->_NbPlayers, _pEngine->_pPlayers);

	WindowPrompt* promptExisting = _pEngine->_pPrompt;
	if (promptExisting)
	{
		pPrompt->SetPrompt(promptExisting);
		pPrompt->SetEngine(_pEngine);
	}

	_pEngine->UnregisterPromptWindow();
	L_HRESULT res = _pEngine->RegisterPromptWindow(pPrompt);
	if (L_E_FAIL == res)
	{
		delete pPrompt;
		pPrompt = NULL;
	}
}

void Tdf_Debug::AdjacentAreas()
{
	if (NULL == _pEngine)
		return;

	int width = 0, height = 0;
	SDL_GetWindowSize(_pEngine->_pMainWindow, &width, &height);

	AdjacentAreaDebugPrompt* pPrompt = new AdjacentAreaDebugPrompt(width, height);
	if (NULL == pPrompt)
		return;
	pPrompt->SetGame(_pEngine->_pGame);

	(_pEngine->_pSelection)->Clean();
	_pEngine->UnregisterSelectionPrompt();

	_pEngine->UnregisterPromptWindow();
	L_HRESULT res = _pEngine->RegisterPromptWindow(pPrompt);
	if (L_E_FAIL == res)
	{
		delete pPrompt;
		pPrompt = NULL;
	}
}


Player** Tdf_Debug::GetPlayers()
{
	if (NULL == _pEngine)
		return NULL;

	return _pEngine->_pPlayers;
}