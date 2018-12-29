#pragma once

#include "GraphicElement.h"
#include "Player.h"
#include "SDL.h"
#include "SDL_Image.h"

class BoardPiece : 
	public GraphicElement
{
public:
	static L_HRESULT LoadMedias();
	static void UnloadMedias();
	static SDL_Rect GetOrderPosition(AREA iArea);
	static SDL_Rect GetUnitPosition(AREA iArea);

	BoardPiece(ELEMENTTYPE iType, int iSubType, Player* iOwner, AREA iArea);
	~BoardPiece();

	ELEMENTTYPE GetType() { return _Type; }
	int GetSubType() { return _SubType; }
	Player* GetOwner() { return _pOwner; }
	AREA GetArea() { return _Area; }

	L_HRESULT AddSubElement(ELEMENTTYPE iType, int iSubType, Player* iOwner, AREA iArea);

	void SetPosition(SDL_Rect& iPosition) { _Position = iPosition; }

protected:
	virtual L_HRESULT _Init();

private:
	ELEMENTTYPE _Type;
	int _SubType;
	Player* _pOwner;
	AREA _Area;

	std::vector<BoardPiece*> _SubElements;
};

