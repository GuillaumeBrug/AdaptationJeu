#pragma once

#include "Player.h"
#include "SDL.h"
#include "SDL_Image.h"

class GraphicElement
{
public:
	~GraphicElement();

	L_HRESULT Render(SDL_Surface*& opSurface, SDL_Rect& oPosition);

	SDL_Rect GetPosition() { return _Position; }

protected:
	GraphicElement();

	virtual L_HRESULT _Init() = 0;

	bool _Initialized;
	bool _FreeSurface;

	SDL_Surface* _pSurface;
	SDL_Rect _Position;
};

