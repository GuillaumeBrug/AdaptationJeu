#include "Board.h"
#include "Player.h"

bool Board::IsAreaASea(AREA iArea)
{
	switch (iArea)
	{
	case AREA::BAY_OF_ICE:
	case AREA::THE_SHIVERING_SEA:
	case AREA::THE_NARROW_SEA:
	case AREA::SUNSEAT_SEA:
	case AREA::IRONMANS_BAY:
	case AREA::THE_GOLDEN_SEA:
	case AREA::BLACKWATER_BAY:
	case AREA::SHIPBREAKER_BAY:
	case AREA::SEA_OF_DORNE:
	case AREA::REDWYNE_STRAIGHTS:
	case AREA::WEST_SUMMER_SEA:
	case AREA::EAST_SUMMER_SEA:
		return true;
	}
	return false;
}

bool Board::IsAreaAPort(AREA iArea)
{
	switch (iArea)
	{
	case AREA::WINTERFELL_PORT:
	case AREA::WHITE_HARBOR_PORT:
	case AREA::IRONMANS_BAY_PORT:
	case AREA::LANNISPORT_PORT:
	case AREA::DRAGONSTONE_PORT:
	case AREA::STORMS_END_PORT:
	case AREA::OLDTOWN_PORT:
	case AREA::SUNSPEAR_PORT:
		return true;
	}
	return false;
}

int Board::HasCastle(AREA iArea)
{
	switch (iArea)
	{
	case AREA::WHITE_HARBOR:
	case AREA::MOAT_CAILIN:
	case AREA::FUNTS_FINGER:
	case AREA::THE_EYRIE:
	case AREA::HARRENHAL:
	case AREA::CRACKLAW_POINT:
	case AREA::THE_REACH:
	case AREA::STORMS_END:
	case AREA::YRONWOOD:
	case AREA::STARFALL:
		return 1;
	case AREA::WINTERFELL:
	case AREA::SEAGARD:
	case AREA::PYKE:
	case AREA::RIVERRUN:
	case AREA::LANNISPORT:
	case AREA::DRAGONSTONE:
	case AREA::KNGS_LANDING:
	case AREA::HIGHGARDEN:
	case AREA::OLDTOWN:
	case AREA::SUNSPEAR:
		return 2;
	}
	return 0;
}

int Board::HasBarrels(AREA iArea)
{
	switch (iArea)
	{
	case AREA::WINTERFELL:
	case AREA::THE_STONY_SHORE:
	case AREA::WIDOWS_WATCH:
	case AREA::GREYWATER_WATCH:
	case AREA::SEAGARD:
	case AREA::PYKE:
	case AREA::THE_FINGERS:
	case AREA::THE_MOUNTAINS_OF_THE_MOON:
	case AREA::RIVERRUN:
	case AREA::THE_EYRIE:
	case AREA::DRAGONSTONE:
	case AREA::SEAROAD_MARCHES:
	case AREA::KINGSWOOD:
	case AREA::PRINCES_PASS:
	case AREA::THREE_TOWERS:
	case AREA::SUNSPEAR:
	case AREA::STARFALL:
	case AREA::SALT_SHORE:
		return 1;
	case AREA::LANNISPORT:
	case AREA::BLACKWATER:
	case AREA::HIGHGARDEN:
		return 2;
	}
	return 0;
}

std::string Board::GetAreaName(AREA iArea)
{
	switch (iArea)
	{
	case AREA::CASTLE_BLACK:
		return "Castle Black";
	case AREA::BAY_OF_ICE:
		return "Bay of Ice";
	case AREA::KARHOLD:
		return "Karhold";
	case AREA::WINTERFELL:
		return "Winterfell";
	case AREA::WINTERFELL_PORT:
		return "Winterfell's Port";
	case AREA::THE_STONY_SHORE:
		return "The Stony Shore";
	case AREA::WHITE_HARBOR:
		return "White Harbor";
	case AREA::WHITE_HARBOR_PORT:
		return "White Haror's Port";
	case AREA::THE_SHIVERING_SEA:
		return "The Shivering Sea";
	case AREA::WIDOWS_WATCH:
		return "Widows Watch";
	case AREA::THE_NARROW_SEA:
		return "The Narrow Sea";
	case AREA::GREYWATER_WATCH:
		return "Greywater Watch";
	case AREA::MOAT_CAILIN:
		return "Moat Cailin";
	case AREA::FUNTS_FINGER:
		return "Funt's Finger";
	case AREA::SUNSEAT_SEA:
		return "Sunseat sea";
	case AREA::IRONMANS_BAY:
		return "Ironman's Bay";
	case AREA::IRONMANS_BAY_PORT:
		return "Pyke's Port";
	case AREA::SEAGARD:
		return "Seagard";
	case AREA::THE_FINGERS:
		return "The Fingers";
	case AREA::THE_TWINS:
		return "The Twins";
	case AREA::PYKE:
		return "Pyke";
	case AREA::THE_MOUNTAINS_OF_THE_MOON:
		return "The Mountains of the Moon";
	case AREA::RIVERRUN:
		return "Riverrun";
	case AREA::THE_EYRIE:
		return "The Eyrie";
	case AREA::LANNISPORT:
		return "Lannisport";
	case AREA::LANNISPORT_PORT:
		return "Lannisport's Port";
	case AREA::HARRENHAL:
		return "Harrenhal";
	case AREA::DRAGONSTONE:
		return "Dragonstone";
	case AREA::DRAGONSTONE_PORT:
		return "Dragonstone's Port";
	case AREA::STONEY_SEPT:
		return "Stoney Sept";
	case AREA::CRACKLAW_POINT:
		return "Craclaw Point";
	case AREA::THE_GOLDEN_SEA:
		return "The Golden Sea";
	case AREA::BLACKWATER_BAY:
		return "Blackwater Bay";
	case AREA::SEAROAD_MARCHES:
		return "Searoad Marches";
	case AREA::BLACKWATER:
		return "Blackwater";
	case AREA::KNGS_LANDING:
		return "King's Landing";
	case AREA::KINGSWOOD:
		return "Kingswood";
	case AREA::SHIPBREAKER_BAY:
		return "Shipbreaker Bay";
	case AREA::HIGHGARDEN:
		return "Highgarden";
	case AREA::THE_REACH:
		return "The Reach";
	case AREA::DORNISH_MARCHES:
		return "Dornish Marches";
	case AREA::THE_BONEWAY:
		return "The Boneway";
	case AREA::STORMS_END:
		return "Storms End";
	case AREA::STORMS_END_PORT:
		return "Storms End's Port";
	case AREA::OLDTOWN:
		return "Oldtown";
	case AREA::OLDTOWN_PORT:
		return "Oldtown's Port";
	case AREA::PRINCES_PASS:
		return "Prince's Pass";
	case AREA::SEA_OF_DORNE:
		return "Sea of Dorne";
	case AREA::THREE_TOWERS:
		return "Three Towers";
	case AREA::YRONWOOD:
		return "Yronwood";
	case AREA::SUNSPEAR:
		return "Sunspear";
	case AREA::SUNSPEAR_PORT:
		return "Sunspear's Port";
	case AREA::REDWYNE_STRAIGHTS:
		return "Redwyne Straights";
	case AREA::STARFALL:
		return "Starfall";
	case AREA::SALT_SHORE:
		return "Salt Shore";
	case AREA::THE_ARBOR:
		return "The Arbor";
	case AREA::WEST_SUMMER_SEA:
		return "West Summer Sea";
	case AREA::EAST_SUMMER_SEA:
		return "East Summer Sea";
	}
	return "error";
}

std::vector<AREA> Board::GetAdjacentAreas(AREA iArea)
{
	std::vector<AREA> list;

	switch (iArea)
	{
	case AREA::CASTLE_BLACK:
		list.push_back(BAY_OF_ICE); list.push_back(KARHOLD); list.push_back(WINTERFELL); list.push_back(THE_SHIVERING_SEA);
		break;
	case AREA::BAY_OF_ICE:
		list.push_back(CASTLE_BLACK); list.push_back(THE_STONY_SHORE); list.push_back(WINTERFELL); list.push_back(SUNSEAT_SEA);
		list.push_back(GREYWATER_WATCH); list.push_back(FUNTS_FINGER); list.push_back(WINTERFELL_PORT);
		break;
	case AREA::KARHOLD:
		list.push_back(CASTLE_BLACK); list.push_back(WINTERFELL); list.push_back(THE_SHIVERING_SEA);
		break;
	case AREA::WINTERFELL:
		list.push_back(CASTLE_BLACK); list.push_back(THE_STONY_SHORE); list.push_back(BAY_OF_ICE); list.push_back(KARHOLD); 
		list.push_back(WHITE_HARBOR); list.push_back(THE_SHIVERING_SEA); list.push_back(MOAT_CAILIN);
		break;
	case AREA::WINTERFELL_PORT:
		list.push_back(WINTERFELL); list.push_back(BAY_OF_ICE);
		break;
	case AREA::THE_STONY_SHORE:
		list.push_back(WINTERFELL); list.push_back(BAY_OF_ICE);
		break;
	case AREA::WHITE_HARBOR:
		list.push_back(WINTERFELL); list.push_back(WIDOWS_WATCH); list.push_back(THE_SHIVERING_SEA); list.push_back(THE_NARROW_SEA);
		list.push_back(MOAT_CAILIN);
		break;
	case AREA::WHITE_HARBOR_PORT:
		list.push_back(WHITE_HARBOR); list.push_back(THE_NARROW_SEA);
		break;
	case AREA::THE_SHIVERING_SEA:
		list.push_back(WINTERFELL); list.push_back(KARHOLD); list.push_back(WHITE_HARBOR); list.push_back(WIDOWS_WATCH);
		list.push_back(CASTLE_BLACK); list.push_back(THE_NARROW_SEA);
		break;
	case AREA::WIDOWS_WATCH:
		list.push_back(THE_NARROW_SEA); list.push_back(WHITE_HARBOR); list.push_back(THE_SHIVERING_SEA);
		break;
	case AREA::THE_NARROW_SEA:
		list.push_back(THE_SHIVERING_SEA); list.push_back(WHITE_HARBOR); list.push_back(WIDOWS_WATCH); list.push_back(MOAT_CAILIN);
		list.push_back(THE_TWINS); list.push_back(THE_FINGERS); list.push_back(THE_MOUNTAINS_OF_THE_MOON); list.push_back(THE_EYRIE);
		list.push_back(CRACKLAW_POINT); list.push_back(SHIPBREAKER_BAY); list.push_back(WHITE_HARBOR_PORT);
		break;
	case AREA::GREYWATER_WATCH:
		list.push_back(MOAT_CAILIN); list.push_back(FUNTS_FINGER); list.push_back(IRONMANS_BAY); list.push_back(BAY_OF_ICE);
		list.push_back(SEAGARD);
		break;
	case AREA::MOAT_CAILIN:
		list.push_back(WINTERFELL); list.push_back(WHITE_HARBOR); list.push_back(THE_NARROW_SEA); list.push_back(THE_TWINS);
		list.push_back(SEAGARD); list.push_back(GREYWATER_WATCH);
		break;
	case AREA::FUNTS_FINGER:
		list.push_back(BAY_OF_ICE); list.push_back(GREYWATER_WATCH); list.push_back(IRONMANS_BAY); list.push_back(SUNSEAT_SEA);
		break;
	case AREA::SUNSEAT_SEA:
		list.push_back(BAY_OF_ICE); list.push_back(FUNTS_FINGER); list.push_back(IRONMANS_BAY); list.push_back(THE_GOLDEN_SEA);
		list.push_back(SEAROAD_MARCHES); list.push_back(WEST_SUMMER_SEA);
		break;
	case AREA::IRONMANS_BAY:
		list.push_back(SUNSEAT_SEA); list.push_back(FUNTS_FINGER); list.push_back(GREYWATER_WATCH); list.push_back(SEAGARD);
		list.push_back(RIVERRUN); list.push_back(THE_GOLDEN_SEA); list.push_back(PYKE); list.push_back(IRONMANS_BAY_PORT);
		break;
	case AREA::IRONMANS_BAY_PORT:
		list.push_back(PYKE); list.push_back(IRONMANS_BAY);
		break;
	case AREA::SEAGARD:
		list.push_back(IRONMANS_BAY); list.push_back(GREYWATER_WATCH); list.push_back(MOAT_CAILIN); list.push_back(THE_TWINS);
		list.push_back(RIVERRUN);
		break;
	case AREA::THE_FINGERS:
		list.push_back(THE_NARROW_SEA); list.push_back(THE_MOUNTAINS_OF_THE_MOON); list.push_back(THE_TWINS);
		break;
	case AREA::THE_TWINS:
		list.push_back(MOAT_CAILIN); list.push_back(THE_NARROW_SEA); list.push_back(THE_FINGERS); list.push_back(THE_MOUNTAINS_OF_THE_MOON);
		list.push_back(SEAGARD);
		break;
	case AREA::PYKE:
		list.push_back(IRONMANS_BAY);
		break;
	case AREA::THE_MOUNTAINS_OF_THE_MOON:
		list.push_back(THE_TWINS); list.push_back(THE_FINGERS); list.push_back(THE_NARROW_SEA); list.push_back(THE_EYRIE);
		list.push_back(CRACKLAW_POINT);
		break;
	case AREA::RIVERRUN:
		list.push_back(THE_GOLDEN_SEA); list.push_back(IRONMANS_BAY); list.push_back(SEAGARD); list.push_back(HARRENHAL);
		list.push_back(STONEY_SEPT); list.push_back(LANNISPORT);
		break;
	case AREA::THE_EYRIE:
		list.push_back(THE_MOUNTAINS_OF_THE_MOON); list.push_back(THE_NARROW_SEA);
		break;
	case AREA::LANNISPORT:
		list.push_back(THE_GOLDEN_SEA); list.push_back(RIVERRUN); list.push_back(STONEY_SEPT); list.push_back(SEAROAD_MARCHES);
		break;
	case AREA::LANNISPORT_PORT:
		list.push_back(LANNISPORT); list.push_back(THE_GOLDEN_SEA);
		break;
	case AREA::HARRENHAL:
		list.push_back(BLACKWATER); list.push_back(RIVERRUN); list.push_back(STONEY_SEPT); list.push_back(CRACKLAW_POINT);
		break;
	case AREA::DRAGONSTONE:
		list.push_back(SHIPBREAKER_BAY);
		break;
	case AREA::DRAGONSTONE_PORT:
		list.push_back(DRAGONSTONE); list.push_back(SHIPBREAKER_BAY);
		break;
	case AREA::STONEY_SEPT:
		list.push_back(LANNISPORT); list.push_back(RIVERRUN); list.push_back(HARRENHAL); list.push_back(BLACKWATER);
		list.push_back(SEAROAD_MARCHES);
		break;
	case AREA::CRACKLAW_POINT:
		list.push_back(THE_MOUNTAINS_OF_THE_MOON); list.push_back(THE_NARROW_SEA); list.push_back(HARRENHAL); list.push_back(SHIPBREAKER_BAY);
		list.push_back(BLACKWATER_BAY); list.push_back(KNGS_LANDING); list.push_back(BLACKWATER);
		break;
	case AREA::THE_GOLDEN_SEA:
		list.push_back(SUNSEAT_SEA); list.push_back(IRONMANS_BAY); list.push_back(RIVERRUN); list.push_back(LANNISPORT);
		list.push_back(SEAROAD_MARCHES); list.push_back(LANNISPORT_PORT);
		break;
	case AREA::BLACKWATER_BAY:
		list.push_back(CRACKLAW_POINT); list.push_back(SHIPBREAKER_BAY); list.push_back(KINGSWOOD); list.push_back(KNGS_LANDING);
		break;
	case AREA::SEAROAD_MARCHES:
		list.push_back(SUNSEAT_SEA); list.push_back(THE_GOLDEN_SEA); list.push_back(LANNISPORT); list.push_back(STONEY_SEPT);
		list.push_back(BLACKWATER); list.push_back(THE_REACH); list.push_back(HIGHGARDEN); list.push_back(WEST_SUMMER_SEA);
		break;
	case AREA::BLACKWATER:
		list.push_back(SEAROAD_MARCHES); list.push_back(HARRENHAL); list.push_back(CRACKLAW_POINT); list.push_back(STONEY_SEPT);
		list.push_back(KNGS_LANDING); list.push_back(THE_REACH);
		break;
	case AREA::KNGS_LANDING:
		list.push_back(BLACKWATER); list.push_back(CRACKLAW_POINT); list.push_back(BLACKWATER_BAY); list.push_back(KINGSWOOD);
		list.push_back(THE_REACH);
		break;
	case AREA::KINGSWOOD:
		list.push_back(KNGS_LANDING); list.push_back(BLACKWATER_BAY); list.push_back(SHIPBREAKER_BAY); list.push_back(STORMS_END);
		list.push_back(THE_BONEWAY); list.push_back(THE_REACH);
		break;
	case AREA::SHIPBREAKER_BAY:
		list.push_back(STORMS_END); list.push_back(KINGSWOOD); list.push_back(BLACKWATER_BAY); list.push_back(CRACKLAW_POINT);
		list.push_back(THE_NARROW_SEA); list.push_back(EAST_SUMMER_SEA); list.push_back(STORMS_END_PORT); list.push_back(DRAGONSTONE_PORT);
		list.push_back(DRAGONSTONE);
		break;
	case AREA::HIGHGARDEN:
		list.push_back(WEST_SUMMER_SEA); list.push_back(REDWYNE_STRAIGHTS); list.push_back(SEAROAD_MARCHES); list.push_back(THE_REACH);
		list.push_back(DORNISH_MARCHES); list.push_back(OLDTOWN);
		break;
	case AREA::THE_REACH:
		list.push_back(HIGHGARDEN); list.push_back(SEAROAD_MARCHES); list.push_back(BLACKWATER); list.push_back(KNGS_LANDING);
		list.push_back(KINGSWOOD); list.push_back(THE_BONEWAY); list.push_back(DORNISH_MARCHES);
		break;
	case AREA::DORNISH_MARCHES:
		list.push_back(HIGHGARDEN); list.push_back(THE_REACH); list.push_back(THE_BONEWAY); list.push_back(PRINCES_PASS);
		list.push_back(THREE_TOWERS); list.push_back(OLDTOWN);
		break;
	case AREA::THE_BONEWAY:
		list.push_back(DORNISH_MARCHES); list.push_back(THE_REACH); list.push_back(KINGSWOOD); list.push_back(STORMS_END);
		list.push_back(SEA_OF_DORNE); list.push_back(YRONWOOD); list.push_back(PRINCES_PASS);
		break;
	case AREA::STORMS_END:
		list.push_back(THE_BONEWAY); list.push_back(KINGSWOOD); list.push_back(SHIPBREAKER_BAY); list.push_back(EAST_SUMMER_SEA);
		list.push_back(SEA_OF_DORNE);
		break;
	case AREA::STORMS_END_PORT:
		list.push_back(STORMS_END); list.push_back(SHIPBREAKER_BAY);
		break;
	case AREA::OLDTOWN:
		list.push_back(REDWYNE_STRAIGHTS); list.push_back(HIGHGARDEN); list.push_back(DORNISH_MARCHES); list.push_back(THREE_TOWERS);
		break;
	case AREA::OLDTOWN_PORT:
		list.push_back(OLDTOWN); list.push_back(REDWYNE_STRAIGHTS);
		break;
	case AREA::PRINCES_PASS:
		list.push_back(THREE_TOWERS); list.push_back(DORNISH_MARCHES); list.push_back(THE_BONEWAY); list.push_back(YRONWOOD);
		list.push_back(STARFALL);
		break;
	case AREA::SEA_OF_DORNE:
		list.push_back(THE_BONEWAY); list.push_back(STORMS_END); list.push_back(EAST_SUMMER_SEA); list.push_back(SUNSPEAR);
		list.push_back(YRONWOOD);
		break;
	case AREA::THREE_TOWERS:
		list.push_back(REDWYNE_STRAIGHTS); list.push_back(OLDTOWN); list.push_back(DORNISH_MARCHES); list.push_back(PRINCES_PASS);
		list.push_back(WEST_SUMMER_SEA);
		break;
	case AREA::YRONWOOD:
		list.push_back(PRINCES_PASS); list.push_back(THE_BONEWAY); list.push_back(SEA_OF_DORNE); list.push_back(SUNSPEAR);
		list.push_back(SALT_SHORE); list.push_back(STARFALL);
		break;
	case AREA::SUNSPEAR:
		list.push_back(YRONWOOD); list.push_back(SEA_OF_DORNE); list.push_back(EAST_SUMMER_SEA); list.push_back(SALT_SHORE);
		break;
	case AREA::SUNSPEAR_PORT:
		list.push_back(SUNSPEAR); list.push_back(EAST_SUMMER_SEA);
		break;
	case AREA::REDWYNE_STRAIGHTS:
		list.push_back(WEST_SUMMER_SEA); list.push_back(HIGHGARDEN); list.push_back(OLDTOWN); list.push_back(THREE_TOWERS);
		list.push_back(THE_ARBOR); list.push_back(OLDTOWN_PORT);
		break;
	case AREA::STARFALL:
		list.push_back(WEST_SUMMER_SEA); list.push_back(PRINCES_PASS); list.push_back(YRONWOOD); list.push_back(SALT_SHORE);
		list.push_back(EAST_SUMMER_SEA);
		break;
	case AREA::SALT_SHORE:
		list.push_back(STARFALL); list.push_back(YRONWOOD); list.push_back(SUNSPEAR); list.push_back(EAST_SUMMER_SEA);
		break;
	case AREA::THE_ARBOR:
		list.push_back(REDWYNE_STRAIGHTS); list.push_back(WEST_SUMMER_SEA);
		break;
	case AREA::WEST_SUMMER_SEA:
		list.push_back(SUNSEAT_SEA); list.push_back(SEAROAD_MARCHES); list.push_back(HIGHGARDEN); list.push_back(REDWYNE_STRAIGHTS);
		list.push_back(THE_ARBOR); list.push_back(THREE_TOWERS); list.push_back(STARFALL); list.push_back(EAST_SUMMER_SEA);
		break;
	case AREA::EAST_SUMMER_SEA:
		list.push_back(WEST_SUMMER_SEA); list.push_back(STARFALL); list.push_back(SALT_SHORE); list.push_back(SUNSPEAR);
		list.push_back(SEA_OF_DORNE); list.push_back(STORMS_END); list.push_back(SHIPBREAKER_BAY); list.push_back(SUNSPEAR_PORT);
		break;
	}

	return list;
}

static std::vector<int> xTrack = { 787, 901, 1016, 1127, 1241, 1354 };
static std::vector<int> yTrack = { 3016, 3144, 3268 };

Board::Board(int iNbPlayers, Player* ipPlayers[6]) :_NbPlayers(iNbPlayers)
{
	for (int i = 0; i < _NbPlayers; i++)
		_pPlayers[i] = ipPlayers[i];

	_pMap = NULL;
	_pBaratheonBoard = NULL;
	_pGreyjoyBoard = NULL;
	_pLannisterBoard = NULL;
	_pMartellBoard = NULL;
	_pStarkBoard = NULL;
	_pTyrellBoard = NULL;

	_pSansBold = TTF_OpenFont("OpenSans-Bold.ttf", 40);
	if (NULL == _pSansBold)
	{
		printf("TTF Font could not be loaded! SDL_Error: %s\n", SDL_GetError());
	}
}

Board::~Board()
{
	SDL_FreeSurface(_pMap); _pMap = NULL;
	SDL_FreeSurface(_pBaratheonBoard); _pBaratheonBoard = NULL;
	SDL_FreeSurface(_pGreyjoyBoard); _pGreyjoyBoard = NULL;
	SDL_FreeSurface(_pLannisterBoard); _pLannisterBoard = NULL;
	SDL_FreeSurface(_pMartellBoard); _pMartellBoard = NULL;
	SDL_FreeSurface(_pStarkBoard); _pStarkBoard = NULL;
	SDL_FreeSurface(_pTyrellBoard); _pTyrellBoard = NULL;

	TTF_CloseFont(_pSansBold); _pSansBold = NULL;

	std::vector<BoardPiece*>::iterator it;
	for (it = _Elements.begin(); it != _Elements.end(); it++)
	{
		delete *it;
	}
}

L_HRESULT Board::Init()
{
	_pMap = SDL_LoadBMP("map_reviewed.bmp");
	CHK_AND_RET_HR(_pMap);
	
	_pBaratheonBoard = SDL_LoadBMP("Baratheon_board.bmp");
	CHK_AND_RET_HR(_pBaratheonBoard);
	_pLannisterBoard = SDL_LoadBMP("Lannister_board.bmp");
	CHK_AND_RET_HR(_pLannisterBoard);
	_pStarkBoard = SDL_LoadBMP("Stark_board.bmp");
	CHK_AND_RET_HR(_pStarkBoard);
	if(_NbPlayers > 3)
	{
		_pGreyjoyBoard = SDL_LoadBMP("Greyjoy_board.bmp");
		CHK_AND_RET_HR(_pGreyjoyBoard);
	}
	if (_NbPlayers > 4)
	{
		_pTyrellBoard = SDL_LoadBMP("Tyrell_board.bmp");
		CHK_AND_RET_HR(_pTyrellBoard);
	}
	if (_NbPlayers > 5)
	{
		_pMartellBoard = SDL_LoadBMP("Martell_board.bmp");
		CHK_AND_RET_HR(_pMartellBoard);
	}

	return L_S_OK;
}

L_HRESULT Board::Render(SDL_Surface*& opSurface)
{
	CHK_AND_RET_HR(_pMap);
	CHK_AND_RET_HR(_pStarkBoard);

	SDL_Surface* pResultSurface = SDL_CreateRGBSurface(0, _pMap->clip_rect.w + _pStarkBoard->clip_rect.w, _pMap->clip_rect.h, 32, 0, 0, 0, 0);
	
	// Add the Map
	SDL_BlitSurface(_pMap, NULL, pResultSurface, NULL);

	// Add the Players Board
	for (int i = 0; i < _NbPlayers; i++)
		CHK_SUCCESS(_RenderPlayer(pResultSurface, _pPlayers[i]));
	
	// Render all the Elements registered on the board
	CHK_SUCCESS(_RenderElements(pResultSurface));

	opSurface = pResultSurface;

	return L_S_OK;
}

BoardPiece* Board::RegisterElement(ELEMENTTYPE iEltType, int iSubType, Player* ipPlayer, AREA iArea,
	SDL_Rect* ipPosition)
{
	if (NULL == ipPlayer)
		return NULL;

	BoardPiece* pElement = new BoardPiece(iEltType, iSubType, ipPlayer, iArea);
	if (NULL == pElement)
		return NULL;

	if (ipPosition != NULL)
		pElement->SetPosition(*ipPosition);

	_Elements.push_back(pElement);

	return pElement;
}

BoardPiece* Board::RegisterSuperElement(ELEMENTTYPE iEltType, int iSubType, Player* ipPlayer, AREA iArea, std::vector<int> iSubTypeSubElts)
{
	if (NULL == ipPlayer)
		return NULL;

	BoardPiece* pSuperElement = new BoardPiece(iEltType, iSubType, ipPlayer, iArea);
	if (NULL == pSuperElement)
		return NULL;

	// Create the SubElements
	std::vector<int>::iterator it;
	for (it = iSubTypeSubElts.begin(); it != iSubTypeSubElts.end(); it++)
	{
		CHK_SUCCESS(pSuperElement->AddSubElement(iEltType, *it, ipPlayer, iArea));
	}

	_Elements.push_back(pSuperElement);

	return pSuperElement;
}

L_HRESULT Board::_RenderPlayer(SDL_Surface* ipSurface, Player* ipPlayer)
{
	CHK_AND_RET_HR(ipPlayer);
	CHK_AND_RET_HR(ipSurface);

	// Get the house of the Player
	HOUSE house = ipPlayer->GetHouse();

	// Color of the text is black otherwise if the house is Greyjoy it is white
	SDL_Color color = { 0, 0, 0 }; 
	if (HOUSE::GREYJOY == house)
		color = { 255, 255, 255 };

	// Write the name of the Player
	std::string name = ipPlayer->GetName();
	SDL_Surface* nameSurface = TTF_RenderText_Solid(_pSansBold, name.c_str(), color);
	CHK_AND_RET_HR(nameSurface);

	// Write the number of castles controled by the Player
	int nbCastles = ipPlayer->GetNumberCastles();
	std::string sCastles = std::to_string(nbCastles);
	sCastles.append(" / 7");
	SDL_Surface* castleSurface = TTF_RenderText_Solid(_pSansBold, sCastles.c_str(), color);
	CHK_AND_RET_HR(castleSurface);

	// Write the number of Power tokens owned by the Player
	int nbPower = ipPlayer->GetNumberPower();
	std::string sPower = std::to_string(nbPower);
	SDL_Surface* powerSurface = TTF_RenderText_Solid(_pSansBold, sPower.c_str(), color);
	CHK_AND_RET_HR(powerSurface);

	// Write the number of Barrels owned by the Player
	int nbBarrels = ipPlayer->GetNumberBarrels();
	std::string sBarrels = std::to_string(nbBarrels);
	SDL_Surface* barrelSurface = TTF_RenderText_Solid(_pSansBold, sBarrels.c_str(), color);
	CHK_AND_RET_HR(barrelSurface);

	SDL_Surface* pPlayerBoard = SDL_CreateRGBSurface(0, _pStarkBoard->w, _pStarkBoard->h, 32, 0, 0, 0, 0);
	CHK_AND_RET_HR(pPlayerBoard);
	SDL_Rect boardPos;
	int yPos = 0;
	switch (house)
	{
	case BARATHEON:
		SDL_BlitSurface(_pBaratheonBoard, NULL, pPlayerBoard, NULL);
		yPos = _NbPlayers > 3 ? 3 : 2;
		boardPos = { _pMap->clip_rect.w, 300 + yPos * _pStarkBoard->clip_rect.h, _pStarkBoard->clip_rect.w, _pStarkBoard->clip_rect.h };
		break;
	case GREYJOY:
		SDL_BlitSurface(_pGreyjoyBoard, NULL, pPlayerBoard, NULL);
		boardPos = { _pMap->clip_rect.w, 300 + _pStarkBoard->clip_rect.h, _pStarkBoard->clip_rect.w, _pStarkBoard->clip_rect.h };
		break;
	case LANNISTER:
		SDL_BlitSurface(_pLannisterBoard, NULL, pPlayerBoard, NULL);
		yPos = _NbPlayers > 3 ? 2 : 1;
		boardPos = { _pMap->clip_rect.w, 300 + yPos * _pStarkBoard->clip_rect.h, _pStarkBoard->clip_rect.w, _pStarkBoard->clip_rect.h };
		break;
	case MARTELL:
		SDL_BlitSurface(_pMartellBoard, NULL, pPlayerBoard, NULL);
		boardPos = { _pMap->clip_rect.w, 300 + 5 * _pStarkBoard->clip_rect.h, _pStarkBoard->clip_rect.w, _pStarkBoard->clip_rect.h };
		break;
	case STARK:
		SDL_BlitSurface(_pStarkBoard, NULL, pPlayerBoard, NULL);
		boardPos = { _pMap->clip_rect.w, 300, _pStarkBoard->clip_rect.w, _pStarkBoard->clip_rect.h };
		break;
	case TYRELL:
		SDL_BlitSurface(_pTyrellBoard, NULL, pPlayerBoard, NULL);
		boardPos = { _pMap->clip_rect.w, 300 + 4 * _pStarkBoard->clip_rect.h, _pStarkBoard->clip_rect.w, _pStarkBoard->clip_rect.h };
		break;
	}

	// Put the name on the Player's board
	SDL_Rect namePos = { 350, 10, nameSurface->clip_rect.w, nameSurface->clip_rect.h };
	SDL_BlitSurface(nameSurface, NULL, pPlayerBoard, &namePos);
	SDL_FreeSurface(nameSurface);

	// Put the number of castles on the Player's board
	SDL_Rect castlePos = { 530, 85, castleSurface->clip_rect.w, castleSurface->clip_rect.h };
	SDL_BlitSurface(castleSurface, NULL, pPlayerBoard, &castlePos);
	SDL_FreeSurface(castleSurface);

	// Put the number of power on the Player's board
	SDL_Rect powerPos = { nbPower > 9 ? 568 : 593, 195, powerSurface->clip_rect.w, powerSurface->clip_rect.h };
	SDL_BlitSurface(powerSurface, NULL, pPlayerBoard, &powerPos);
	SDL_FreeSurface(powerSurface);

	// Put the number of barrels on the Player's board
	SDL_Rect barrelPos = { 593, 310, barrelSurface->clip_rect.w, barrelSurface->clip_rect.h };
	SDL_BlitSurface(barrelSurface, NULL, pPlayerBoard, &barrelPos);
	SDL_FreeSurface(barrelSurface);

	// Put the Player's board on the board
	SDL_BlitSurface(pPlayerBoard, NULL, ipSurface, &boardPos);
	SDL_FreeSurface(pPlayerBoard);

	// Put the Player house token in the influence tracks
	int throneIndex = ipPlayer->GetThronePosition();
	SDL_Rect thronePos = { xTrack[throneIndex - 1], yTrack[0], 84, 84 };
	RegisterElement(INFLUENCE, house, ipPlayer, (AREA)0, &thronePos);

	int fiefIndex = ipPlayer->GetFiefPosition();
	SDL_Rect fiefPos = { xTrack[fiefIndex - 1], yTrack[1], 84, 84 };
	RegisterElement(INFLUENCE, house, ipPlayer, (AREA)1, &fiefPos);

	int courtIndex = ipPlayer->GetCourtPosition();
	SDL_Rect courtPos = { xTrack[courtIndex - 1], yTrack[2], 84, 84 };
	RegisterElement(INFLUENCE, house, ipPlayer, (AREA)0, &courtPos);

	return L_S_OK;
}

L_HRESULT Board::_RenderElements(SDL_Surface* ipSurface)
{
	CHK_AND_RET_HR(ipSurface);

	std::vector<BoardPiece*>::iterator it;
	for (it = _Elements.begin(); it != _Elements.end(); it++)
	{
		BoardPiece* pElement = *it;
		CHK_AND_RET_HR(pElement);

		SDL_Surface* pEltSurface = NULL;
		SDL_Rect eltPos = { 0, 0, 0, 0 };
		pElement->Render(pEltSurface, eltPos);
		CHK_AND_RET_HR(pEltSurface);

		// Put the element Surface on the board
		SDL_BlitSurface(pEltSurface, NULL, ipSurface, &eltPos);
	}

	return L_S_OK;
}

L_HRESULT Board::RemoveElement(ELEMENTTYPE iEltType, Player* ipPlayer, AREA iArea)
{
	CHK_AND_RET_HR(ipPlayer);

	std::vector<BoardPiece*>::iterator it;
	for (it = _Elements.begin(); it != _Elements.end(); it++)
	{
		if (iArea == (*it)->GetArea() && iEltType == (*it)->GetType() && ipPlayer == (*it)->GetOwner())
		{
			_Elements.erase(it);
			break;
		}
	}

	return L_S_OK;
}

L_HRESULT Board::RemoveElement(BoardPiece* ipBoardPiece)
{
	CHK_AND_RET_HR(ipBoardPiece);

	std::vector<BoardPiece*>::iterator it;
	for (it = _Elements.begin(); it != _Elements.end(); it++)
	{
		if (ipBoardPiece == *it)
		{
			_Elements.erase(it);
			return L_S_OK;
		}
	}

	return L_E_FAIL;
}

BoardPiece* Board::GetElementAt(ELEMENTTYPE iEltType, AREA iArea)
{
	std::vector<BoardPiece*>::iterator it;
	for (it = _Elements.begin(); it != _Elements.end(); it++)
	{
		if (iEltType == (*it)->GetType() && iArea == (*it)->GetArea())
			return *it;
	}
}
