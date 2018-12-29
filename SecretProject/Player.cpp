#include "Player.h"
#include "Board.h"
#include <algorithm>

Player::Player(std::string iName):_Name(iName), _House(HOUSE::UNDEFINED), _NbPowerTokens(0),
_pBoard(NULL)
{
}

Player::~Player()
{
	_pBoard = NULL;
}

L_HRESULT Player::Init(HOUSE iHouse)
{
	_House = iHouse;
	_NbPowerTokens = 5;
	_AvailableUnits.insert(std::pair<int, int>(UNIT::FOOTMAN, 10));
	_AvailableUnits.insert(std::pair<int, int>(UNIT::KNIGHT, 5));
	_AvailableUnits.insert(std::pair<int, int>(UNIT::ENGINE, 2));
	_AvailableUnits.insert(std::pair<int, int>(UNIT::SHIP, 6));

	// Setup differs depending on the House
	switch (_House)
	{
	case HOUSE::BARATHEON:
		_AddUnitInArea(UNIT::FOOTMAN, AREA::DRAGONSTONE);
		_AddUnitInArea(UNIT::KNIGHT, AREA::DRAGONSTONE);
		_AddUnitInArea(UNIT::FOOTMAN, AREA::KINGSWOOD);
		_AddUnitInArea(UNIT::SHIP, AREA::SHIPBREAKER_BAY);
		_AddUnitInArea(UNIT::SHIP, AREA::SHIPBREAKER_BAY);

		_ThronePosition = 1;
		_FiefPosition = 5;
		_CourtPosition = 4;
		break;
	case HOUSE::GREYJOY:
		_AddUnitInArea(UNIT::FOOTMAN, AREA::PYKE);
		_AddUnitInArea(UNIT::KNIGHT, AREA::PYKE);
		_AddUnitInArea(UNIT::FOOTMAN, AREA::GREYWATER_WATCH);
		_AddUnitInArea(UNIT::SHIP, AREA::IRONMANS_BAY);
		_AddUnitInArea(UNIT::SHIP, AREA::IRONMANS_BAY_PORT);

		_ThronePosition = 5;
		_FiefPosition = 1;
		_CourtPosition = 6;
		break;
	case HOUSE::LANNISTER:
		_AddUnitInArea(UNIT::FOOTMAN, AREA::LANNISPORT);
		_AddUnitInArea(UNIT::KNIGHT, AREA::LANNISPORT);
		_AddUnitInArea(UNIT::FOOTMAN, AREA::STONEY_SEPT);
		_AddUnitInArea(UNIT::SHIP, AREA::THE_GOLDEN_SEA);

		_ThronePosition = 2;
		_FiefPosition = 6;
		_CourtPosition = 1;
		break;
	case HOUSE::MARTELL:
		_AddUnitInArea(UNIT::FOOTMAN, AREA::SUNSPEAR);
		_AddUnitInArea(UNIT::KNIGHT, AREA::SUNSPEAR);
		_AddUnitInArea(UNIT::FOOTMAN, AREA::SALT_SHORE);
		_AddUnitInArea(UNIT::SHIP, AREA::SEA_OF_DORNE);

		_ThronePosition = 4;
		_FiefPosition = 3;
		_CourtPosition = 3;
		break;
	case HOUSE::STARK:
		_AddUnitInArea(UNIT::FOOTMAN, AREA::WINTERFELL);
		_AddUnitInArea(UNIT::KNIGHT, AREA::WINTERFELL);
		_AddUnitInArea(UNIT::FOOTMAN, AREA::WHITE_HARBOR);
		_AddUnitInArea(UNIT::SHIP, AREA::THE_SHIVERING_SEA);

		_ThronePosition = 3;
		_FiefPosition = 4;
		_CourtPosition = 2;
		break;
	case HOUSE::TYRELL:
		_AddUnitInArea(UNIT::FOOTMAN, AREA::HIGHGARDEN);
		_AddUnitInArea(UNIT::KNIGHT, AREA::HIGHGARDEN);
		_AddUnitInArea(UNIT::FOOTMAN, AREA::DORNISH_MARCHES);
		_AddUnitInArea(UNIT::SHIP, AREA::REDWYNE_STRAIGHTS);

		_ThronePosition = 6;
		_FiefPosition = 2;
		_CourtPosition = 5;
		break;
	}

	return L_S_OK;
}

int Player::GetNumberCastles()
{
	int nbCastles = 0;

	std::vector<int>::iterator it;
	for (it = _ControledAreas.begin(); it != _ControledAreas.end(); it++)
	{
		if (Board::HasCastle((AREA)*it))
			nbCastles++;
	}

	return nbCastles;
}

int Player::GetNumberBarrels()
{
	int nbBarrels = 0;

	std::vector<int>::iterator it;
	for (it = _ControledAreas.begin(); it != _ControledAreas.end(); it++)
	{
		nbBarrels += Board::HasBarrels((AREA)*it);			
	}

	return nbBarrels;
}

bool Player::HasRaidOrderToPlay()
{
	std::map<int, int>::iterator it;
	for (it = _PlannedOrders.begin(); it != _PlannedOrders.end(); it++)
	{
		if (ORDER::RAID_1 == (ORDER)it->first || ORDER::RAID_2 == (ORDER)it->first || ORDER::RAID_STAR == (ORDER)it->first)
			return true;
	}

	return false;
}

bool Player::HasMarchOrderToPlay()
{
	std::map<int, int>::iterator it;
	for (it = _PlannedOrders.begin(); it != _PlannedOrders.end(); it++)
	{
		if (ORDER::MARCH == (ORDER)it->first || ORDER::MARCH_MINUS== (ORDER)it->first || ORDER::MARCH_STAR== (ORDER)it->first)
			return true;
	}

	return false;
}

bool Player::HasConsolidateOrderToPlay()
{
	std::map<int, int>::iterator it;
	for (it = _PlannedOrders.begin(); it != _PlannedOrders.end(); it++)
	{
		if (ORDER::CONSOLIDATE_1 == (ORDER)it->first || ORDER::CONSOLIDATE_2 == (ORDER)it->first || ORDER::CONSOLIDATE_STAR== (ORDER)it->first)
			return true;
	}

	return false;
}

int Player::UnitStillAvailable(UNIT iUnit)
{
	std::map<int, int>::iterator it = _AvailableUnits.find(iUnit);
	if (it == _AvailableUnits.end())
		return 0;

	return it->second;
}

std::vector<AREA> Player::GetAreasWithUnits()
{
	std::vector<AREA> oAreas;

	std::map<int, std::vector<int>>::iterator it;
	for (it = _DeployedUnits.begin(); it != _DeployedUnits.end(); it++)
		oAreas.push_back((AREA)it->first);

	return oAreas;
}

std::vector<UNIT> Player::GetUnitsOnArea(AREA iArea)
{
	std::vector<UNIT> oUnits;

	std::map<int, std::vector<int>>::iterator it = _DeployedUnits.find(iArea);
	if (it == _DeployedUnits.end())
		return oUnits;

	std::vector<int>::iterator itUnits;
	for(itUnits = _DeployedUnits[iArea].begin(); itUnits != _DeployedUnits[iArea].end(); itUnits++)
		oUnits.push_back((UNIT)(*itUnits));

	return oUnits;
}

std::vector<ORDER> Player::GetPlannedOrders()
{
	std::vector<ORDER> results;

	std::map<int, int>::iterator it;
	for (it = _PlannedOrders.begin(); it != _PlannedOrders.end(); it++)
		results.push_back((ORDER)it->first);

	return results;
}

bool LargestToSmallest(int i, int j) { return (i > j); }

L_HRESULT Player::_AddUnitInArea(UNIT iUnit, AREA iArea)
{
	CHK_AND_RET_HR(_pBoard);

	if (!UnitStillAvailable(iUnit))
		return L_E_FAIL;

	std::map<int, std::vector<int>>::iterator it = _DeployedUnits.find(iArea);
	if (it == _DeployedUnits.end())
	{
		std::vector<int> listUnits;
		listUnits.push_back(iUnit);
		CHK_SUCCESS(_RemoveUnitFromStock(iUnit));
		_DeployedUnits.insert(std::pair<int, std::vector<int>>(iArea, listUnits));

		// No unit was in this Are before, means the Player has earned it control
		_ControledAreas.push_back(iArea);

		CHK_AND_RET_HR(_pBoard->RegisterElement(UNITTYPE, iUnit, this, iArea));
	}
	else
	{
		_DeployedUnits[iArea].push_back(iUnit);
		CHK_SUCCESS(_RemoveUnitFromStock(iUnit));

		CHK_SUCCESS(_pBoard->RemoveElement(UNITTYPE, this, iArea));

		std::sort(_DeployedUnits[iArea].begin(), _DeployedUnits[iArea].end(), LargestToSmallest);
		CHK_AND_RET_HR(_pBoard->RegisterSuperElement(UNITTYPE, ARMY, this, iArea, _DeployedUnits[iArea]));
	}

	return L_S_OK;
}

L_HRESULT Player::_RemoveUnitFromStock(UNIT iUnit)
{
	std::map<int, int>::iterator it = _AvailableUnits.find(iUnit);
	if (it == _AvailableUnits.end())
		return L_E_FAIL;

	int nbAvailable = it->second;
	nbAvailable--;
	_AvailableUnits[iUnit] = nbAvailable;

	return L_S_OK;
}

L_HRESULT Player::_RemoveAllUnitsFromArea(AREA iArea)
{
	std::map<int, std::vector<int>>::iterator it = _DeployedUnits.find(iArea);
	if (it != _DeployedUnits.end())
	{
		std::vector<int>::iterator itUnit;
		for (itUnit = (it->second).begin(); itUnit != (it->second).end(); itUnit++)
		{
			int unit = (*itUnit);
			_ReturnUnitToStock((UNIT)unit);
		}
		(it->second).empty();

		CHK_SUCCESS(_pBoard->RemoveElement(UNITTYPE, this, iArea));

		std::remove(_ControledAreas.begin(), _ControledAreas.end(), iArea);
		_ControledAreas.erase(_ControledAreas.end() - 1);

		_DeployedUnits.erase(iArea);
	}

	return L_S_OK;
}

L_HRESULT Player::_ReturnUnitToStock(UNIT iUnit)
{
	std::map<int, int>::iterator it = _AvailableUnits.find(iUnit);
	if (it == _AvailableUnits.end())
		return L_E_FAIL;

	int nbAvailable = it->second;
	nbAvailable++;
	_AvailableUnits[iUnit] = nbAvailable;

	return L_S_OK;
}

L_HRESULT Player::AddOrderInArea(ORDER iOrder, AREA iArea)
{
	// Look if iArea already has an Order planned
	std::map<int, int>::iterator itArea;
	for (itArea = _PlannedOrders.begin(); itArea != _PlannedOrders.end(); itArea++)
	{
		if (iArea == (AREA)itArea->second)
		{
			CHK_SUCCESS(_RemovePlannedOrder((ORDER)itArea->first));
			break;
		}
	}

	// Remove iOrder if planned somewhere else
	_RemovePlannedOrder(iOrder);

	// Planned iOrder in iArea
	_PlannedOrders[iOrder] = iArea;

	CHK_AND_RET_HR(_pBoard->RegisterElement(ORDERTYPE, iOrder, this, iArea));

	return L_S_OK;
}

L_HRESULT Player::_RemovePlannedOrder(ORDER iOrder)
{
	std::map<int, int>::iterator it = _PlannedOrders.find(iOrder);
	if (it == _PlannedOrders.end())
		return L_E_FAIL;

	CHK_SUCCESS(_pBoard->RemoveElement(ORDERTYPE, this, (AREA)it->second));

	_PlannedOrders.erase(iOrder);

	return L_S_OK;
}

std::vector<AREA> Player::GetAreaRaidOrders()
{
	std::vector<AREA> areas;

	std::map<int, int>::iterator it;
	for (it = _PlannedOrders.begin(); it != _PlannedOrders.end(); it++)
	{
		if (ORDER::RAID_1 == (ORDER)it->first || ORDER::RAID_2 == (ORDER)it->first || ORDER::RAID_STAR == (ORDER)it->first)
			areas.push_back((AREA)it->second);
	}

	return areas;
}

std::vector<AREA> Player::GetAreaMarchOrders()
{
	std::vector<AREA> areas;

	std::map<int, int>::iterator it;
	for (it = _PlannedOrders.begin(); it != _PlannedOrders.end(); it++)
	{
		if (ORDER::MARCH_MINUS == (ORDER)it->first || ORDER::MARCH == (ORDER)it->first || ORDER::MARCH_STAR == (ORDER)it->first)
			areas.push_back((AREA)it->second);
	}

	return areas;
}

L_HRESULT Player::RemoveOrderInArea(ORDER iOrder, AREA iArea)
{
	std::map<int, int>::iterator itArea;
	for (itArea = _PlannedOrders.begin(); itArea != _PlannedOrders.end(); itArea++)
	{
		if (iArea == (AREA)itArea->second)
		{
			CHK_SUCCESS(_RemovePlannedOrder((ORDER)itArea->first));
			return L_S_OK;
		}
	}

	return L_E_FAIL;
}

void Player::AddPowerTokens(int iNbPower)
{
	_NbPowerTokens += iNbPower;
	if (_MarkedAreas.size() + _NbPowerTokens > 20)
		_NbPowerTokens = 20 - _MarkedAreas.size();
}

void Player::RemovePowerTokens(int iNbPower)
{
	_NbPowerTokens -= iNbPower;
	if (_NbPowerTokens < 0)
		_NbPowerTokens = 0;
}