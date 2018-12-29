#pragma once
#include "Tdf_Defs.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_TTF.h"
#include "BoardPiece.h"
#include <string>

class Player;

class Board
{
public:

	static bool IsAreaASea(AREA iArea); // Returns true if the Area is a Sea
	static bool IsAreaAPort(AREA iArea); // Returns true if the Area is a Port
	static int HasCastle(AREA iArea); // Returns 0 if not, 1 if castle, 2 if stronghlod
	static int HasBarrels(AREA iArea); // Returns the number of Barrels
	static std::string GetAreaName(AREA iArea); // Returns the name of an Area
	static std::vector<AREA> GetAdjacentAreas(AREA iArea); // Returns the adjacent Areas of an Area

	Board(int iNbPlayers, Player* ipPlayers[6]);
	~Board();

	L_HRESULT Init();

	L_HRESULT Render(SDL_Surface*& opSurface);

	BoardPiece* RegisterElement(ELEMENTTYPE iEltType, int iSubType, Player* ipPlayer, AREA iArea,
		SDL_Rect* ipPosition = NULL);
	
	BoardPiece* RegisterSuperElement(ELEMENTTYPE iEltType, int iSubType, Player* ipPlayer, AREA iArea, std::vector<int> iSubTypeSubElts);

	L_HRESULT RemoveElement(ELEMENTTYPE iEltType, Player* ipPlayer, AREA iArea);

	L_HRESULT RemoveElement(BoardPiece* ipBoardPiece);

	BoardPiece* GetElementAt(ELEMENTTYPE iEltType, AREA iArea);

private:
	L_HRESULT _RenderPlayer(SDL_Surface* ipSurface, Player* ipPlayer);

	L_HRESULT _RenderElements(SDL_Surface* ipSurface);

	int _NbPlayers;
	Player* _pPlayers[6];
	std::vector<BoardPiece*> _Elements;

	TTF_Font* _pSansBold;

	SDL_Surface* _pMap;
	SDL_Surface* _pBaratheonBoard;
	SDL_Surface* _pGreyjoyBoard;
	SDL_Surface* _pLannisterBoard;
	SDL_Surface* _pMartellBoard;
	SDL_Surface* _pStarkBoard;
	SDL_Surface* _pTyrellBoard;
};

