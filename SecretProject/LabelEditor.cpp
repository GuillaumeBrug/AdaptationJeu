#include "LabelEditor.h"
#include "SDL_image.h"
#include "SDL_TTF.h"

LabelEditor::LabelEditor(LABELTYPE iType, int iID):WindowElement(iID), _Type(iType)
{
}

LabelEditor::~LabelEditor()
{
}

L_HRESULT LabelEditor::_Init()
{
	SDL_Surface* pBack = NULL;
	switch (_Type)
	{
	case EDITOR:
		break;
	case LABEL:
		pBack = IMG_Load("LabelBack.png");
		break;
	}

	SDL_Color color = { 105, 105, 105 };
	TTF_Font* pSansBold = TTF_OpenFont("OpenSans-Bold.ttf", 40);
	CHK_AND_RET_HR(pSansBold);

	SDL_Surface* pTexteSurface = TTF_RenderText_Solid(pSansBold, _Texte.c_str(), color);
	CHK_AND_RET_HR(pTexteSurface);

	if (_PositionForced)
		_pSurface = SDL_CreateRGBSurface(0, _Position.w, _Position.h, 32, 0, 0, 0, 0);
	else
		_pSurface = SDL_CreateRGBSurface(0, pBack->w, pBack->h, 32, 0, 0, 0, 0);

	SDL_BlitScaled(pBack, NULL, _pSurface, NULL);
	SDL_FreeSurface(pBack);

	SDL_Rect posTexte;
	if(pTexteSurface->w >= _pSurface->w /*- 10*/)
	{
		posTexte = { 5, _pSurface->h / 2 - pTexteSurface->h / 2, _pSurface->w - 10 , pTexteSurface->h };
	}
	else
	{
		posTexte = { _pSurface->w / 2 - pTexteSurface->w / 2, _pSurface->h / 2 - pTexteSurface->h / 2, pTexteSurface->w , pTexteSurface->h };
	}

	SDL_BlitScaled(pTexteSurface, NULL, _pSurface, &posTexte);
	SDL_FreeSurface(pTexteSurface);

	TTF_CloseFont(pSansBold);
	pSansBold = NULL;

	return L_S_OK;
}
