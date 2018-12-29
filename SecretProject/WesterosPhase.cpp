#include "WesterosPhase.h"

WesterosPhase::WesterosPhase(Game* ipGame):GameState(ipGame)
{
}

WesterosPhase::~WesterosPhase()
{
}

L_HRESULT WesterosPhase::Init()
{
	return L_S_OK;
}

L_HRESULT WesterosPhase::Activate()
{
	return L_S_OK;
}

L_HRESULT WesterosPhase::Deactivate()
{
	return L_S_OK;
}

GameState* WesterosPhase::_GetNextState()
{
	return NULL;
}
