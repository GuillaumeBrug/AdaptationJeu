#include "GraphicElement.h"
#include "SDL.h"

GraphicElement::GraphicElement(): _pSurface(NULL), _FreeSurface(true)
{
}

GraphicElement::~GraphicElement()
{
	if(_FreeSurface && _pSurface)
		SDL_FreeSurface(_pSurface);
	_pSurface = NULL;
}

L_HRESULT GraphicElement::Render(SDL_Surface*& opSurface, SDL_Rect& oPosition)
{
	if (!_Initialized)
	{
		if (_pSurface)
			SDL_FreeSurface(_pSurface);
		_pSurface = NULL;

		CHK_SUCCESS(_Init());
		CHK_AND_RET_HR(_pSurface);
		_Initialized = true;
	}

	opSurface = _pSurface;
	oPosition = _Position;

	return L_S_OK;
}

bool GraphicElement::HasBeenClicked(int iX, int iY)
{
	//printf("Is Element %d  at {%d, %d} sized {%d, %d} clicked ?", _ID, _Position.x, _Position.y, _Position.w, _Position.h);

	bool inX = iX >= _Position.x && iX <= _Position.x + _Position.w;
	bool inY = iY >= _Position.y && iY <= _Position.y + _Position.h;
	/*if (inX && inY)
		printf(" YES\n");
	else
		printf(" NO\n");*/
	return inX && inY;
}
