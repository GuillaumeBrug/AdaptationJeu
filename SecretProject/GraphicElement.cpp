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
		if (NULL == _pSurface)
			int i = 0;
		CHK_AND_RET_HR(_pSurface);
		_Initialized = true;
	}

	opSurface = _pSurface;
	oPosition = _Position;

	return L_S_OK;
}
