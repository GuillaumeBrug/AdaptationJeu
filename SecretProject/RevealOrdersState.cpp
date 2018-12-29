#include "RevealOrdersState.h"

RevealOrdersState::RevealOrdersState(Game* ipGame):GameState(ipGame)
{
}

RevealOrdersState::~RevealOrdersState()
{
}

L_HRESULT RevealOrdersState::Init()
{
	return L_S_OK;
}

L_HRESULT RevealOrdersState::Activate()
{
	_Activated = true;
	return L_S_OK;
}

L_HRESULT RevealOrdersState::Deactivate()
{
	_Activated = false;
	_Completed = false;
	return L_S_OK;
}

L_HRESULT RevealOrdersState::Execute()
{
	_Completed = true;
	return L_S_OK;
}
