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

	int GetThronePosition() { return _ThronePosition; }
	void SetThronePosition(int iPosition) { _ThronePosition = iPosition; }
	int GetFiefPosition() { return _FiefPosition; }
	void SetFiefPosition(int iPosition) { _FiefPosition = iPosition; }
	int GetCourtPosition() { return _CourtPosition; }
	void SetCourtPosition(int iPosition) { _CourtPosition = iPosition; }

	bool HasRaidOrderToPlay();
	bool HasMarchOrderToPlay();
	bool HasConsolidateOrderToPlay();

	int UnitStillAvailable(UNIT iUnit);

	std::vector<AREA> GetAreasWithUnits();
	std::vector<UNIT> GetUnitsOnArea(AREA iArea);

	L_HRESULT AddOrderInArea(ORDER iOrder, AREA iArea);
	std::vector<ORDER> GetPlannedOrders();
	std::vector<AREA> GetAreaRaidOrders();
	std::vector<AREA> GetAreaMarchOrders();
	L_HRESULT RemoveOrderInArea(ORDER iOrder, AREA iArea);

	void AddPowerTokens(int iNbPower);
	void RemovePowerTokens(int iNbPower);

private:
	L_HRESULT _AddUnitInArea(UNIT iUnit, AREA iArea);
	L_HRESULT _RemoveUnitFromStock(UNIT iUnit);
	L_HRESULT _RemoveAllUnitsFromArea(AREA iArea);
	L_HRESULT _ReturnUnitToStock(UNIT iUnit);

	L_HRESULT _RemovePlannedOrder(ORDER iOrder);

	Board* _pBoard;

	std::string _Name;
	HOUSE _House;
	int _NbPowerTokens;
	int _ThronePosition;
	int _FiefPosition;
	int _CourtPosition;

	std::map<int, int> _PlannedOrders;
	std::map<int, std::vector<int>> _DeployedUnits;
	std::map<int, int> _AvailableUnits;
	std::vector<int> _MarkedAreas;
	std::vector<int> _ControledAreas;

	friend class AddUnitDebugPrompt;
	friend class AddOrderDebugPrompt;
};

