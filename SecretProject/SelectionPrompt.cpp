#include "SelectionPrompt.h"
#include "Player.h"
#include "Board.h"
#include "GraphicElement.h"

SelectionPrompt::SelectionPrompt(SELECTTYPE iType, Board* ipBoard, Player* ipPlayer):_Type(iType), 
_SelectedArea(UNDEFINED_AREA), _pPlayer(ipPlayer), _pBoard(ipBoard)
{
}

SelectionPrompt::~SelectionPrompt()
{
	Clean();

	_pPlayer = NULL;
	_pBoard = NULL;
}

L_HRESULT SelectionPrompt::Init(std::vector<AREA> iAreas)
{
	CHK_AND_RET_HR(_pBoard);
	CHK_AND_RET_HR(_pPlayer);

	std::vector<AREA>::iterator it;
	for (it = iAreas.begin(); it != iAreas.end(); it++)
	{
		SDL_Rect position;
		switch (_Type)
		{
		case SELECTORDER:
		{
			position = BoardPiece::GetOrderPosition(*it);
			break;
		}
		case SELECTUNIT:
		{
			position = BoardPiece::GetUnitPosition(*it);
			position.x -= 40;
			position.y -= 5;
			break;
		}
		}

		BoardPiece* pElement = _pBoard->RegisterElement(SELECTER, _Type, _pPlayer, *it, &position);
		CHK_AND_RET_HR(pElement);

		_Selecters.push_back(pElement);
	}

	return L_S_OK;
}

L_HRESULT SelectionPrompt::AddSelecter(SELECTTYPE iType, AREA iArea)
{
	CHK_AND_RET_HR(_pBoard);
	BoardPiece* pPiece = _pBoard->GetElementAt(SELECTER, iArea);
	if (NULL != pPiece)
		return L_E_FAIL;

	SDL_Rect position;
	switch (iType)
	{
	case SELECTORDER:
		position = BoardPiece::GetOrderPosition(iArea);
		break;
	case SELECTUNIT:
		position = BoardPiece::GetUnitPosition(iArea);
		position.x -= 40;
		position.y -= 5;
		position.h = 175;
		position.w = 125;
		break;
	}

	BoardPiece* pElement = _pBoard->RegisterElement(SELECTER, iType, _pPlayer, iArea, &position);
	CHK_AND_RET_HR(pElement);

	_Selecters.push_back(pElement);

	return L_S_OK;
}

L_HRESULT SelectionPrompt::InputClick(int iX, int iY)
{
	std::vector<BoardPiece*>::iterator it;
	for (it = _Selecters.begin(); it != _Selecters.end(); it++)
	{
		if ((*it)->HasBeenClicked(iX, iY))
		{
			_SelectedArea = (*it)->GetArea();
			break;
		}
	}
	return L_S_OK;
}

void SelectionPrompt::Clean()
{
	if (NULL == _pBoard)
		return;

	std::vector<BoardPiece*>::iterator it;
	for (it = _Selecters.begin(); it != _Selecters.end(); it++)
	{
		if (*it)
		{
			_pBoard->RemoveElement(*it);
			delete *it;
		}
	}
	_Selecters.clear();

	_SelectedArea = UNDEFINED_AREA;
}
