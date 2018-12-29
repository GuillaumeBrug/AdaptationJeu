#pragma once

#include "WindowPrompt.h"

class MarchMovementsPrompt :
	public WindowPrompt
{
public:
	MarchMovementsPrompt(int iWinWidth, int iWinHeight);
	~MarchMovementsPrompt();

	L_HRESULT AddMovement(AREA iArea, std::vector<UNIT> iMove);

	void RemoveMovement(AREA iArea);

	bool GetMovement(AREA iArea, std::vector<UNIT> oMove);

	std::map<AREA, std::vector<UNIT>> GetMovements() { return _mapMovements; }

private:
	bool _HasMoveOnArea(AREA iArea);

	std::map<AREA, std::vector<UNIT>> _mapMovements;
};

