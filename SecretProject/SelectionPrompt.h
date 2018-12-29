#pragma once

#include "Tdf_Defs.h"
#include <vector>

class Board;
class Player;
class BoardPiece;

class SelectionPrompt
{
public:
	SelectionPrompt(SELECTTYPE iType, Board* ipBoard, Player* ipPlayer);
	~SelectionPrompt();

	L_HRESULT Init(std::vector<AREA> iAreas);

	L_HRESULT AddSelecter(SELECTTYPE iType, AREA iArea);

	L_HRESULT InputClick(int iX, int iY);

	AREA GetSelectedArea() { return _SelectedArea; }

	void Clean();

private:
	SELECTTYPE _Type;
	Player* _pPlayer;
	Board* _pBoard;
	std::vector<BoardPiece*> _Selecters;

	AREA _SelectedArea;
};

