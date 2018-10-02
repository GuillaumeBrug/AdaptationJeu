#include "Tdf_Debug.h"
#include "Engine.h"
#include "SDL_syswm.h"
#include "resource.h"
#include "AddUnitDebugPrompt.h"
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

	L_HRESULT res = _pEngine->RegisterPromptWindow(pPrompt);
	if (L_E_FAIL == res)
	{
		delete pPrompt;
		pPrompt = NULL;
	}
}

void Tdf_Debug::AddOrderInArea()
{
}


Player** Tdf_Debug::GetPlayers()
{
	if (NULL == _pEngine)
		return NULL;

	return _pEngine->_pPlayers;
}