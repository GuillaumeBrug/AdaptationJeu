#include "BoardPiece.h"
#include "SDL.h"

static SDL_Surface* _pMarchMinus;
static SDL_Surface* _pMarch;
static SDL_Surface* _pMarchStar;
static SDL_Surface* _pDefense;
static SDL_Surface* _pDefenseStar;
static SDL_Surface* _pRaid;
static SDL_Surface* _pRaidStar;
static SDL_Surface* _pConsolidate;
static SDL_Surface* _pConsolidateStar;
static SDL_Surface* _pSupport;
static SDL_Surface* _pSupportStar;

static SDL_Surface* _pFootBara;
static SDL_Surface* _pKnightBara;
static SDL_Surface* _pEngineBara;
static SDL_Surface* _pShipBara;
static SDL_Surface* _pFootGrey;
static SDL_Surface* _pKnightGrey;
static SDL_Surface* _pEngineGrey;
static SDL_Surface* _pShipGrey;
static SDL_Surface* _pFootLan;
static SDL_Surface* _pKnightLan;
static SDL_Surface* _pEngineLan;
static SDL_Surface* _pShipLan;
static SDL_Surface* _pFootMar;
static SDL_Surface* _pKnightMar;
static SDL_Surface* _pEngineMar;
static SDL_Surface* _pShipMar;
static SDL_Surface* _pFootStark;
static SDL_Surface* _pKnightStark;
static SDL_Surface* _pEngineStark;
static SDL_Surface* _pShipStark;
static SDL_Surface* _pFootTyr;
static SDL_Surface* _pKnightTyr;
static SDL_Surface* _pEngineTyr;
static SDL_Surface* _pShipTyr;

static SDL_Surface* _pInflBara;
static SDL_Surface* _pInflGrey;
static SDL_Surface* _pInflLan;
static SDL_Surface* _pInflMar;
static SDL_Surface* _pInflStark;
static SDL_Surface* _pInflTyr;

static SDL_Surface* _pSelectOrder;
static SDL_Surface* _pSelectArea;

L_HRESULT BoardPiece::LoadMedias()
{
	_pMarchMinus = IMG_Load("MarchMinusOrder.png");
	CHK_AND_RET_HR(_pMarchMinus);
	_pMarch = IMG_Load("MarchOrder.png");
	CHK_AND_RET_HR(_pMarch);
	_pMarchStar = IMG_Load("MarchPlusOrder.png");
	CHK_AND_RET_HR(_pMarchStar);
	_pDefense = IMG_Load("DefenseOrder.png");
	CHK_AND_RET_HR(_pDefense);
	_pDefenseStar = IMG_Load("DefensePlusOrder.png");
	CHK_AND_RET_HR(_pDefenseStar);
	_pRaid = IMG_Load("RaidOrder.png");
	CHK_AND_RET_HR(_pRaid);
	_pRaidStar = IMG_Load("RaidStarOrder.png");
	CHK_AND_RET_HR(_pRaidStar);
	_pConsolidate = IMG_Load("ConsolidateOrder.png");
	CHK_AND_RET_HR(_pConsolidate);
	_pConsolidateStar = IMG_Load("ConsolidateStarOrder.png");
	CHK_AND_RET_HR(_pConsolidateStar);
	_pSupport = IMG_Load("SupportOrder.png");
	CHK_AND_RET_HR(_pSupport);
	_pSupportStar = IMG_Load("SupportStarOrder.png");
	CHK_AND_RET_HR(_pSupportStar);

	_pFootBara = IMG_Load("Fanta_Bara.png");
	CHK_AND_RET_HR(_pFootBara);
	_pKnightBara = IMG_Load("Chev_Bara.png");
	CHK_AND_RET_HR(_pKnightBara);
	_pEngineBara = IMG_Load("Rook_Bara.png");
	CHK_AND_RET_HR(_pEngineBara);
	_pShipBara = IMG_Load("Boat_Bara.png");
	CHK_AND_RET_HR(_pShipBara);
	_pFootGrey = IMG_Load("Fanta_Grey.png");
	CHK_AND_RET_HR(_pFootGrey);
	_pKnightGrey = IMG_Load("Chev_Grey.png");
	CHK_AND_RET_HR(_pKnightGrey);
	_pEngineGrey = IMG_Load("Rook_Grey.png");
	CHK_AND_RET_HR(_pEngineGrey);
	_pShipGrey = IMG_Load("Boat_Grey.png");
	CHK_AND_RET_HR(_pShipGrey);
	_pFootLan = IMG_Load("Fanta_Lan.png");
	CHK_AND_RET_HR(_pFootLan);
	_pKnightLan = IMG_Load("Chev_Lan.png");
	CHK_AND_RET_HR(_pKnightLan);
	_pEngineLan = IMG_Load("Rook_Lan.png");
	CHK_AND_RET_HR(_pEngineLan);
	_pShipLan = IMG_Load("Boat_Lan.png");
	CHK_AND_RET_HR(_pShipLan);
	_pFootMar = IMG_Load("Fanta_Mar.png");
	CHK_AND_RET_HR(_pFootMar);
	_pKnightMar = IMG_Load("Chev_Mar.png");
	CHK_AND_RET_HR(_pKnightMar);
	_pEngineMar = IMG_Load("Rook_Mar.png");
	CHK_AND_RET_HR(_pEngineMar);
	_pShipMar = IMG_Load("Boat_Mar.png");
	CHK_AND_RET_HR(_pShipMar);
	_pFootStark = IMG_Load("Fanta_Stark.png");
	CHK_AND_RET_HR(_pFootStark);
	_pKnightStark = IMG_Load("Chev_Stark.png");
	CHK_AND_RET_HR(_pKnightStark);
	_pEngineStark = IMG_Load("Rook_Stark.png");
	CHK_AND_RET_HR(_pEngineStark);
	_pShipStark = IMG_Load("Boat_Stark.png");
	CHK_AND_RET_HR(_pShipStark);
	_pFootTyr = IMG_Load("Fanta_Tyr.png");
	CHK_AND_RET_HR(_pFootTyr);
	_pKnightTyr = IMG_Load("Chev_Tyr.png");
	CHK_AND_RET_HR(_pKnightTyr);
	_pEngineTyr = IMG_Load("Rook_Tyr.png");
	CHK_AND_RET_HR(_pEngineTyr);
	_pShipTyr = IMG_Load("Boat_Tyr.png");
	CHK_AND_RET_HR(_pShipTyr);

	_pInflBara = IMG_Load("Influence_Baratheon.png");
	CHK_AND_RET_HR(_pInflBara);
	_pInflGrey = IMG_Load("Influence_Greyjoy.png");
	CHK_AND_RET_HR(_pInflGrey);
	_pInflLan = IMG_Load("Influence_Lannister.png");
	CHK_AND_RET_HR(_pInflLan);
	_pInflMar = IMG_Load("Influence_Martell.png");
	CHK_AND_RET_HR(_pInflMar);
	_pInflStark = IMG_Load("Influence_Stark.png");
	CHK_AND_RET_HR(_pInflStark);
	_pInflTyr = IMG_Load("Influence_Tyrell.png");
	CHK_AND_RET_HR(_pInflTyr);

	_pSelectOrder = IMG_Load("SelectOrder.png");
	CHK_AND_RET_HR(_pSelectOrder);
	_pSelectArea = IMG_Load("SelectArea.png");
	CHK_AND_RET_HR(_pSelectArea);

	return L_S_OK;
}

void BoardPiece::UnloadMedias()
{
	SDL_FreeSurface(_pMarchMinus); _pMarchMinus = NULL;
	SDL_FreeSurface(_pMarch); _pMarch = NULL;
	SDL_FreeSurface(_pMarchStar); _pMarchStar = NULL;
	SDL_FreeSurface(_pDefense); _pDefense = NULL;
	SDL_FreeSurface(_pDefenseStar); _pDefenseStar = NULL;
	SDL_FreeSurface(_pRaid); _pRaid = NULL;
	SDL_FreeSurface(_pRaidStar); _pRaidStar = NULL;
	SDL_FreeSurface(_pConsolidate); _pConsolidate = NULL;
	SDL_FreeSurface(_pConsolidateStar); _pConsolidateStar = NULL;
	SDL_FreeSurface(_pSupport); _pSupport = NULL;
	SDL_FreeSurface(_pSupportStar); _pSupportStar = NULL;

	SDL_FreeSurface(_pFootBara); _pFootBara = NULL;
	SDL_FreeSurface(_pKnightBara); _pKnightBara = NULL;
	SDL_FreeSurface(_pEngineBara); _pEngineBara = NULL;
	SDL_FreeSurface(_pShipBara); _pShipBara = NULL;
	SDL_FreeSurface(_pFootGrey); _pFootGrey = NULL;
	SDL_FreeSurface(_pKnightGrey); _pKnightGrey = NULL;
	SDL_FreeSurface(_pEngineGrey); _pEngineGrey = NULL;
	SDL_FreeSurface(_pShipGrey); _pShipGrey = NULL;
	SDL_FreeSurface(_pFootLan); _pFootLan = NULL;
	SDL_FreeSurface(_pKnightLan); _pKnightLan = NULL;
	SDL_FreeSurface(_pEngineLan); _pEngineLan = NULL;
	SDL_FreeSurface(_pShipLan); _pShipLan = NULL;
	SDL_FreeSurface(_pFootMar); _pFootMar = NULL;
	SDL_FreeSurface(_pKnightMar); _pKnightMar = NULL;
	SDL_FreeSurface(_pEngineMar); _pEngineMar = NULL;
	SDL_FreeSurface(_pShipMar); _pShipMar = NULL;
	SDL_FreeSurface(_pFootStark); _pFootStark = NULL;
	SDL_FreeSurface(_pKnightStark); _pKnightStark = NULL;
	SDL_FreeSurface(_pEngineStark); _pEngineStark = NULL;
	SDL_FreeSurface(_pShipStark); _pShipStark = NULL;
	SDL_FreeSurface(_pFootTyr); _pFootTyr = NULL;
	SDL_FreeSurface(_pKnightTyr); _pKnightTyr = NULL;
	SDL_FreeSurface(_pEngineTyr); _pEngineTyr = NULL;
	SDL_FreeSurface(_pShipTyr); _pShipTyr = NULL;
	
	SDL_FreeSurface(_pInflBara); _pInflBara = NULL;
	SDL_FreeSurface(_pInflGrey); _pInflGrey = NULL;
	SDL_FreeSurface(_pInflLan); _pInflLan = NULL;
	SDL_FreeSurface(_pInflMar); _pInflMar = NULL;
	SDL_FreeSurface(_pInflStark); _pInflStark = NULL;
	SDL_FreeSurface(_pInflTyr); _pInflTyr = NULL;
}

SDL_Rect BoardPiece::GetOrderPosition(AREA iArea)
{
	SDL_Rect position = { 0, 0, 0, 0 };

	switch (iArea)
	{
	case CASTLE_BLACK:
		position = { 766, 226, 100, 100 };
		break;
	case BAY_OF_ICE:
		position = { 90, 615, 100, 100 };
		break;
	case KARHOLD:
		position = { 1070, 435, 100, 100 };
		break;
	case WINTERFELL:
		position = { 680, 535, 100, 100 };
		break;
	case WINTERFELL_PORT:
		position = { 370, 405, 100, 100 };
		break;
	case THE_STONY_SHORE:
		position = { 299, 774, 100, 100 };
		break;
	case WHITE_HARBOR:
		position = { 881, 700, 100, 100 };
		break;
	case WHITE_HARBOR_PORT:
		position = { 865, 1115, 100, 100 };
		break;
	case THE_SHIVERING_SEA:
		position = { 1280, 715, 100, 100 };
		break;
	case WIDOWS_WATCH:
		position = { 1010, 875, 100, 100 };
		break;
	case THE_NARROW_SEA:
		position = { 1297, 1215, 100, 100 };
		break;
	case GREYWATER_WATCH:
		position = { 470, 1175, 100, 100 };
		break;
	case MOAT_CAILIN:
		position = { 665, 1075, 100, 100 };
		break;
	case FUNTS_FINGER:
		position = { 174, 1120, 100, 100 };
		break;
	case SUNSEAT_SEA:
		position = { 105, 1950, 100, 100 };
		break;
	case IRONMANS_BAY:
		position = { 95, 1470, 100, 100 };
		break;
	case IRONMANS_BAY_PORT:
		position = { 245, 1330, 100, 100 };
		break;
	case SEAGARD:
		position = { 511, 1290, 100, 100 };
		break;
	case THE_FINGERS:
		position = { 920, 1255, 100, 100 };
		break;
	case THE_TWINS:
		position = { 747, 1255, 100, 100 };
		break;
	case PYKE:
		position = { 210, 1385, 100, 100 };
		break;
	case THE_MOUNTAINS_OF_THE_MOON:
		position = { 815, 1430, 100, 100 };
		break;
	case RIVERRUN:
		position = { 520, 1535, 100, 100 };
		break;
	case THE_EYRIE:
		position = { 1020, 1545, 100, 100 };
		break;
	case LANNISPORT:
		position = { 375, 1600, 100, 100 };
		break;
	case LANNISPORT_PORT:
		position = { 131, 1705, 100, 100 };
		break;
	case HARRENHAL:
		position = { 746, 1615, 100, 100 };
		break;
	case DRAGONSTONE:
		position = { 1325, 1795, 100, 100 };
		break;
	case DRAGONSTONE_PORT:
		position = { 1285, 1905, 100, 100 };
		break;
	case STONEY_SEPT:
		position = { 486, 1765, 100, 100 };
		break;
	case CRACKLAW_POINT:
		position = { 875, 1705, 100, 100 };
		break;
	case THE_GOLDEN_SEA:
		position = { 51, 1815, 100, 100 };
		break;
	case BLACKWATER_BAY:
		position = { 1100, 1775, 100, 100 };
		break;
	case SEAROAD_MARCHES:
		position = { 241, 1995, 100, 100 };
		break;
	case BLACKWATER:
		position = { 570, 1945, 100, 100 };
		break;
	case KNGS_LANDING:
		position = { 915, 1875, 100, 100 };
		break;
	case KINGSWOOD:
		position = { 1015, 2075, 100, 100 };
		break;
	case SHIPBREAKER_BAY:
		position = { 1357, 2090, 100, 100 };
		break;
	case HIGHGARDEN:
		position = { 405, 2245, 100, 100 };
		break;
	case THE_REACH:
		position = { 535, 2130, 100, 100 };
		break;
	case DORNISH_MARCHES:
		position = { 490, 2315, 100, 100 };
		break;
	case THE_BONEWAY:
		position = { 785, 2425, 100, 100 };
		break;
	case STORMS_END:
		position = { 1015, 2275, 100, 100 };
		break;
	case STORMS_END_PORT:
		position = { 1225, 2250, 100, 100 };
		break;
	case OLDTOWN:
		position = { 286, 2355, 100, 100 };
		break;
	case OLDTOWN_PORT:
		position = { 165, 2305, 100, 100 };
		break;
	case PRINCES_PASS:
		position = { 551, 2515, 100, 100 };
		break;
	case SEA_OF_DORNE:
		position = { 985, 2445, 100, 100 };
		break;
	case THREE_TOWERS:
		position = { 381, 2470, 100, 100 };
		break;
	case YRONWOOD:
		position = { 820, 2560, 100, 100 };
		break;
	case SUNSPEAR:
		position = { 1039, 2580, 100, 100 };
		break;
	case SUNSPEAR_PORT:
		position = { 1305, 2560, 100, 100 };
		break;
	case REDWYNE_STRAIGHTS:
		position = { 105, 2515, 100, 100 };
		break;
	case STARFALL:
		position = { 480, 2665, 100, 100 };
		break;
	case SALT_SHORE:
		position = { 810, 2690, 100, 100 };
		break;
	case THE_ARBOR:
		position = { 35, 2750, 100, 100 };
		break;
	case WEST_SUMMER_SEA:
		position = { 260, 2815, 100, 100 };
		break;
	case EAST_SUMMER_SEA:
		position = { 1170, 2765, 100, 100 };
		break;
	}

	return position;
}

SDL_Rect BoardPiece::GetUnitPosition(AREA iArea)
{
	SDL_Rect position = { 0, 0, 0, 0 };

	switch (iArea)
	{
	case CASTLE_BLACK:
		position = { 886, 266, 100, 100 };
		break;
	case BAY_OF_ICE:
		position = { 90, 535, 100, 100 };
		break;
	case KARHOLD:
		position = { 1190, 435, 100, 100 };
		break;
	case WINTERFELL:
		position = { 800, 535, 100, 100 };
		break;
	case WINTERFELL_PORT:
		position = { 370, 485, 100, 100 };
		break;
	case THE_STONY_SHORE:
		position = { 379, 814, 100, 100 };
		break;
	case WHITE_HARBOR:
		position = { 841, 780, 100, 100 };
		break;
	case WHITE_HARBOR_PORT:
		position = { 865, 1035, 100, 100 };
		break;
	case THE_SHIVERING_SEA:
		position = { 1280, 635, 100, 100 };
		break;
	case WIDOWS_WATCH:
		position = { 1010, 795, 100, 100 };
		break;
	case THE_NARROW_SEA:
		position = { 1297, 1135, 100, 100 };
		break;
	case GREYWATER_WATCH:
		position = { 470, 1095, 100, 100 };
		break;
	case MOAT_CAILIN:
		position = { 625, 1155, 100, 100 };
		break;
	case FUNTS_FINGER:
		position = { 274, 1120, 100, 100 };
		break;
	case SUNSEAT_SEA:
		position = { 25, 1950, 100, 100 };
		break;
	case IRONMANS_BAY:
		position = { 95, 1550, 100, 100 };
		break;
	case IRONMANS_BAY_PORT:
		position = { 325, 1330, 100, 100 };
		break;
	case SEAGARD:
		position = { 511, 1370, 100, 100 };
		break;
	case THE_FINGERS:
		position = { 1000, 1255, 100, 100 };
		break;
	case THE_TWINS:
		position = { 707, 1335, 100, 100 };
		break;
	case PYKE:
		position = { 250, 1465, 100, 100 };
		break;
	case THE_MOUNTAINS_OF_THE_MOON:
		position = { 895, 1430, 100, 100 };
		break;
	case RIVERRUN:
		position = { 600, 1535, 100, 100 };
		break;
	case THE_EYRIE:
		position = { 1100, 1545, 100, 100 };
		break;
	case LANNISPORT:
		position = { 375, 1680, 100, 100 };
		break;
	case LANNISPORT_PORT:
		position = { 211, 1705, 100, 100 };
		break;
	case HARRENHAL:
		position = { 746, 1695, 100, 100 };
		break;
	case DRAGONSTONE:
		position = { 1325, 1715, 100, 100 };
		break;
	case DRAGONSTONE_PORT:
		position = { 1365, 1905, 100, 100 };
		break;
	case STONEY_SEPT:
		position = { 566, 1765, 100, 100 };
		break;
	case CRACKLAW_POINT:
		position = { 955, 1745, 100, 100 };
		break;
	case THE_GOLDEN_SEA:
		position = { 91, 1855, 100, 100 };
		break;
	case BLACKWATER_BAY:
		position = { 1100, 1855, 100, 100 };
		break;
	case SEAROAD_MARCHES:
		position = { 321, 1995, 100, 100 };
		break;
	case BLACKWATER:
		position = { 690, 1905, 100, 100 };
		break;
	case KNGS_LANDING:
		position = { 915, 1955, 100, 100 };
		break;
	case KINGSWOOD:
		position = { 935, 2115, 100, 100 };
		break;
	case SHIPBREAKER_BAY:
		position = { 1277, 2090, 100, 100 };
		break;
	case HIGHGARDEN:
		position = { 345, 2165, 100, 100 };
		break;
	case THE_REACH:
		position = { 615, 2130, 100, 100 };
		break;
	case DORNISH_MARCHES:
		position = { 590, 2275, 100, 100 };
		break;
	case THE_BONEWAY:
		position = { 785, 2345, 100, 100 };
		break;
	case STORMS_END:
		position = { 1015, 2195, 100, 100 };
		break;
	case STORMS_END_PORT:
		position = { 1145, 2250, 100, 100 };
		break;
	case OLDTOWN:
		position = { 286, 2435, 100, 100 };
		break;
	case OLDTOWN_PORT:
		position = { 165, 2385, 100, 100 };
		break;
	case PRINCES_PASS:
		position = { 551, 2435, 100, 100 };
		break;
	case SEA_OF_DORNE:
		position = { 1085, 2445, 100, 100 };
		break;
	case THREE_TOWERS:
		position = { 381, 2550, 100, 100 };
		break;
	case YRONWOOD:
		position = { 720, 2560, 100, 100 };
		break;
	case SUNSPEAR:
		position = { 1139, 2580, 100, 100 };
		break;
	case SUNSPEAR_PORT:
		position = { 1305, 2640, 100, 100 };
		break;
	case REDWYNE_STRAIGHTS:
		position = { 105, 2595, 100, 100 };
		break;
	case STARFALL:
		position = { 580, 2665, 100, 100 };
		break;
	case SALT_SHORE:
		position = { 910, 2650, 100, 100 };
		break;
	case THE_ARBOR:
		position = { 135, 2750, 100, 100 };
		break;
	case WEST_SUMMER_SEA:
		position = { 360, 2815, 100, 100 };
		break;
	case EAST_SUMMER_SEA:
		position = { 1270, 2765, 100, 100 };
		break;
	}

	return position;
}

BoardPiece::BoardPiece(ELEMENTTYPE iType, int iSubType, Player* iOwner, AREA iArea):GraphicElement(),
	_Type(iType), _SubType(iSubType), _pOwner(iOwner), _Area(iArea)
{
	_FreeSurface = false;
}

BoardPiece::~BoardPiece()
{
	int size = _SubElements.size();
	if (size)
	{
		SDL_FreeSurface(_pSurface);

		std::vector<BoardPiece*>::iterator it;
		for (it = _SubElements.begin(); it != _SubElements.end(); it++)
		{
			delete *it;
		}
	}
}

L_HRESULT BoardPiece::AddSubElement(ELEMENTTYPE iType, int iSubType, Player* iOwner, AREA iArea)
{
	CHK_AND_RET_HR(iOwner);

	BoardPiece* pSubElement = new BoardPiece(iType, iSubType, iOwner, iArea);
	CHK_AND_RET_HR(pSubElement);

	_SubElements.push_back(pSubElement);

	return L_S_OK;
}

L_HRESULT BoardPiece::_Init()
{
	if (NULL == _pOwner)
		return L_E_FAIL;

	int size = _SubElements.size();
	if (size)
	{
		// This is a Super Element
		_pSurface = SDL_CreateRGBSurface(0, 200, 200, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
		CHK_AND_RET_HR(_pSurface);

		std::vector<BoardPiece*>::iterator it;
		int index = 0;
		for (it = _SubElements.begin(); it != _SubElements.end(); it++)
		{
			index++;
			SDL_Surface* pSubSurface = NULL;
			(*it)->Render(pSubSurface, _Position);
			CHK_AND_RET_HR(pSubSurface);

			SDL_Rect shift = {50, 0, _Position.w, _Position.h };
			if (2 == index)
			{
				if(size > 3)
					shift.x += 2 * shift.w / 3;
				else
				{
					shift.x -= shift.w / 3;
					shift.y += shift.h / 3;
				}
			}
			else if (3 == index)
			{
				if (size > 3)
				{
					shift.x -= shift.w / 3;
					shift.y += shift.h / 3;
				}
				else
				{
					shift.x += shift.w / 3;
					shift.y += shift.h / 3;
				}
			}
			else if (4 == index)
			{
				shift.x += shift.w / 3;
				shift.y += shift.h / 3;
			}
			else if(index > 4)
				continue;

			SDL_BlitSurface(pSubSurface, NULL, _pSurface, &shift);
		}
		_Position.x -= 50;
		_Position.w = 200;
		_Position.h = 200;
	}
	else
	{
		HOUSE house = _pOwner->GetHouse();

		switch (_Type)
		{
		case UNITTYPE:
			switch (_SubType)
			{
			case FOOTMAN:
				switch (house)
				{
				case BARATHEON:
					_pSurface = _pFootBara;
					break;
				case GREYJOY:
					_pSurface = _pFootGrey;
					break;
				case LANNISTER:
					_pSurface = _pFootLan;
					break;
				case MARTELL:
					_pSurface = _pFootMar;
					break;
				case STARK:
					_pSurface = _pFootStark;
					break;
				case TYRELL:
					_pSurface = _pFootTyr;
					break;
				}
				break;
			case KNIGHT:
				switch (house)
				{
				case BARATHEON:
					_pSurface = _pKnightBara;
					break;
				case GREYJOY:
					_pSurface = _pKnightGrey;
					break;
				case LANNISTER:
					_pSurface = _pKnightLan;
					break;
				case MARTELL:
					_pSurface = _pKnightMar;
					break;
				case STARK:
					_pSurface = _pKnightStark;
					break;
				case TYRELL:
					_pSurface = _pKnightTyr;
					break;
				}
				break;
			case ENGINE:
				switch (house)
				{
				case BARATHEON:
					_pSurface = _pEngineBara;
					break;
				case GREYJOY:
					_pSurface = _pEngineGrey;
					break;
				case LANNISTER:
					_pSurface = _pEngineLan;
					break;
				case MARTELL:
					_pSurface = _pEngineMar;
					break;
				case STARK:
					_pSurface = _pEngineStark;
					break;
				case TYRELL:
					_pSurface = _pEngineTyr;
					break;
				}
				break;
			case SHIP:
				switch (house)
				{
				case BARATHEON:
					_pSurface = _pShipBara;
					break;
				case GREYJOY:
					_pSurface = _pShipGrey;
					break;
				case LANNISTER:
					_pSurface = _pShipLan;
					break;
				case MARTELL:
					_pSurface = _pShipMar;
					break;
				case STARK:
					_pSurface = _pShipStark;
					break;
				case TYRELL:
					_pSurface = _pShipTyr;
					break;
				}
				break;
			}

			_Position = GetUnitPosition(_Area);
			break;
		case ORDERTYPE:
			switch ((ORDER)_SubType)
			{
			case MARCH_MINUS:
				_pSurface = _pMarchMinus;
				break;
			case MARCH:
				_pSurface = _pMarch;
				break;
			case MARCH_STAR:
				_pSurface = _pMarchStar;
				break;
			case SUPPORT_1:
			case SUPPORT_2:
				_pSurface = _pSupport;
				break;
			case SUPPORT_STAR:
				_pSurface = _pSupportStar;
				break;
			case DEFENSE_1:
			case DEFENSE_2:
				_pSurface = _pDefense;
				break;
			case DEFENSE_STAR:
				_pSurface = _pDefenseStar;
				break;
			case CONSOLIDATE_1:
			case CONSOLIDATE_2:
				_pSurface = _pConsolidate;
				break;
			case CONSOLIDATE_STAR:
				_pSurface = _pConsolidateStar;
				break;
			case RAID_1:
			case RAID_2:
				_pSurface = _pRaid;
				break;
			case RAID_STAR:
				_pSurface = _pRaidStar;
				break;
			}
			
			_Position = GetOrderPosition(_Area);
			break;
		case POWER:
			switch (_Area)
			{
			case CASTLE_BLACK:
				_Position = { 0, 0, 0, 0 };
				break;
			case BAY_OF_ICE:
				_Position = { 0, 0, 0, 0 };
				break;
			case KARHOLD:
				_Position = { 0, 0, 0, 0 };
				break;
			case THE_STONY_SHORE:
				_Position = { 0, 0, 0, 0 };
				break;
			case WHITE_HARBOR:
				_Position = { 0, 0, 0, 0 };
				break;
			case THE_SHIVERING_SEA:
				_Position = { 0, 0, 0, 0 };
				break;
			case WIDOWS_WATCH:
				_Position = { 0, 0, 0, 0 };
				break;
			case THE_NARROW_SEA:
				_Position = { 0, 0, 0, 0 };
				break;
			case GREYWATER_WATCH:
				_Position = { 0, 0, 0, 0 };
				break;
			case MOAT_CAILIN:
				_Position = { 0, 0, 0, 0 };
				break;
			case FUNTS_FINGER:
				_Position = { 0, 0, 0, 0 };
				break;
			case SUNSEAT_SEA:
				_Position = { 0, 0, 0, 0 };
				break;
			case IRONMANS_BAY:
				_Position = { 0, 0, 0, 0 };
				break;
			case SEAGARD:
				_Position = { 0, 0, 0, 0 };
				break;
			case THE_FINGERS:
				_Position = { 0, 0, 0, 0 };
				break;
			case THE_TWINS:
				_Position = { 0, 0, 0, 0 };
				break;
			case THE_MOUNTAINS_OF_THE_MOON:
				_Position = { 0, 0, 0, 0 };
				break;
			case RIVERRUN:
				_Position = { 0, 0, 0, 0 };
				break;
			case THE_EYRIE:
				_Position = { 0, 0, 0, 0 };
				break;
			case HARRENHAL:
				_Position = { 0, 0, 0, 0 };
				break;
			case STONEY_SEPT:
				_Position = { 0, 0, 0, 0 };
				break;
			case CRACKLAW_POINT:
				_Position = { 0, 0, 0, 0 };
				break;
			case THE_GOLDEN_SEA:
				_Position = { 0, 0, 0, 0 };
				break;
			case BLACKWATER_BAY:
				_Position = { 0, 0, 0, 0 };
				break;
			case SEAROAD_MARCHES:
				_Position = { 0, 0, 0, 0 };
				break;
			case BLACKWATER:
				_Position = { 0, 0, 0, 0 };
				break;
			case KNGS_LANDING:
				_Position = { 0, 0, 0, 0 };
				break;
			case KINGSWOOD:
				_Position = { 0, 0, 0, 0 };
				break;
			case SHIPBREAKER_BAY:
				_Position = { 0, 0, 0, 0 };
				break;
			case THE_REACH:
				_Position = { 0, 0, 0, 0 };
				break;
			case DORNISH_MARCHES:
				_Position = { 0, 0, 0, 0 };
				break;
			case THE_BONEWAY:
				_Position = { 0, 0, 0, 0 };
				break;
			case STORMS_END:
				_Position = { 0, 0, 0, 0 };
				break;
			case OLDTOWN:
				_Position = { 0, 0, 0, 0 };
				break;
			case PRINCES_PASS:
				_Position = { 0, 0, 0, 0 };
				break;
			case SEA_OF_DORNE:
				_Position = { 0, 0, 0, 0 };
				break;
			case THREE_TOWERS:
				_Position = { 0, 0, 0, 0 };
				break;
			case YRONWOOD:
				_Position = { 0, 0, 0, 0 };
				break;
			case REDWYNE_STRAIGHTS:
				_Position = { 0, 0, 0, 0 };
				break;
			case STARFALL:
				_Position = { 0, 0, 0, 0 };
				break;
			case SALT_SHORE:
				_Position = { 0, 0, 0, 0 };
				break;
			case THE_ARBOR:
				_Position = { 0, 0, 0, 0 };
				break;
			case WEST_SUMMER_SEA:
				_Position = { 0, 0, 0, 0 };
				break;
			case EAST_SUMMER_SEA:
				_Position = { 0, 0, 0, 0 };
				break;
			}
			break;
		case GARNISON:
			break;
		case NEUTRAL:
			break;
		case WILDLING:
			break;
		case INFLUENCE:
			switch ((HOUSE)_SubType)
			{
			case BARATHEON:
				_pSurface = _pInflBara;
				break;
			case GREYJOY:
				_pSurface = _pInflGrey;
				break;
			case LANNISTER:
				_pSurface = _pInflLan;
				break;
			case MARTELL:
				_pSurface = _pInflMar;
				break;
			case STARK:
				_pSurface = _pInflStark;
				break;
			case TYRELL:
				_pSurface = _pInflTyr;
				break;
			}
			break;
		case SELECTER:
			switch ((SELECTTYPE)_SubType)
			{
			case SELECTORDER:
				_pSurface = _pSelectOrder;
				break;
			case SELECTUNIT:
				_pSurface = _pSelectArea;
				break;
			}
			break;
		}
	}

	CHK_AND_RET_HR(_pSurface);

	return L_S_OK;
}
