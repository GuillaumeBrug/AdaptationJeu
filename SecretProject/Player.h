#pragma once

#include <string>
#include "Tdf_Defs.h"
#include <map>
#include <vector>

class Board;

class Player
{
public:
	Player(std::string iName);
	~Player();

	L_HRESULT Init(HOUSE iHouse);

	void SetBoard(Board* ipBoard) { _pBoard = ipBoard; }

	std::string GetName() { return _Name; }
	HOUSE GetHouse() { return _House; }

	int GetNumberCastles();
	int GetNumberBarrels();
	int GetNumberPower() { return _NbPowerTokens; }

	bool HasRaidOrderToPlay();
	bool HasMarchOrderToPlay();
	bool HasConsolidateOrderToPlay();

	int UnitStillAvailable(UNIT iUnit);

private:
	L_HRESULT _AddUnitInArea(UNIT iUnit, AREA iArea);
	L_HRESULT _RemoveUnitFromStock(UNIT iUnit);
	L_HRESULT _RemoveAllUnitsFromArea(AREA iArea);
	L_HRESULT _ReturnUnitToStock(UNIT iUnit);

	Board* _pBoard;

	std::string _Name;
	HOUSE _House;
	int _NbPowerTokens;

	std::map<int, int> _PlannedOrders;
	std::map<int, std::vector<int>> _DeployedUnits;
	std::map<int, int> _AvailableUnits;
	std::vector<int> _MarkedAreas;
	std::vector<int> _ControledAreas;

	friend class AddUnitDebugPrompt;
};

