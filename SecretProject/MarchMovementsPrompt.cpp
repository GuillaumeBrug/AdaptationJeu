#include "MarchMovementsPrompt.h"

MarchMovementsPrompt::MarchMovementsPrompt(int iWinWidth, int iWinHeight):WindowPrompt(iWinWidth, iWinHeight)
{
}

MarchMovementsPrompt::~MarchMovementsPrompt()
{
}

L_HRESULT MarchMovementsPrompt::AddMovement(AREA iArea, std::vector<UNIT> iMove)
{
	if (_HasMoveOnArea(iArea))
		return L_E_FAIL;

	_mapMovements.insert(std::pair<AREA, std::vector<UNIT>>(iArea, iMove));

	return L_S_OK;
}

void MarchMovementsPrompt::RemoveMovement(AREA iArea)
{
	if (_HasMoveOnArea(iArea))
		_mapMovements.erase(iArea);
}

bool MarchMovementsPrompt::GetMovement(AREA iArea, std::vector<UNIT> oMove)
{
	if (!_HasMoveOnArea(iArea))
		return false;

	oMove = _mapMovements[iArea];

	return true;
}

bool MarchMovementsPrompt::_HasMoveOnArea(AREA iArea)
{
	std::map<AREA, std::vector<UNIT>>::iterator it = _mapMovements.find(iArea);
	if (it != _mapMovements.end())
		return true;
	else
		return false;
}
