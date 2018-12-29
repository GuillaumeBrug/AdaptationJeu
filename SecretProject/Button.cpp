#include "Button.h"
#include "SDL_image.h"
#include "SDL_TTF.h"

Button::Button(BUTTONTYPE iType, std::string iTexteOrName, int iID):WindowElement(iID),
_eType(iType), _CheckMode(false), _Checked(false)
{
	switch (_eType)
	{
	case TEXTE:
		_Texte = iTexteOrName;
		break;
	case IMAGE:
		_Image = iTexteOrName;
		break;
	}
}

Button::~Button()
{
}

void Button::SetCheckState(bool iCheckState)
{
	if (_Checked != iCheckState)
	{
		_Checked = iCheckState;
		_Initialized = false;
	}
}

L_HRESULT Button::_Init()
{
	switch (_eType)
	{
	case TEXTE:
	{
		SDL_Surface* pButtonBack = NULL;
		if (_Checked)
			pButtonBack = IMG_Load("ButtonBackChecked.png");
		else
			pButtonBack = IMG_Load("ButtonBack.png");
		CHK_AND_RET_HR(pButtonBack);

		SDL_Color color = { 0, 0, 255 };
		TTF_Font* pSansBold = TTF_OpenFont("OpenSans-Bold.ttf", 40);
		CHK_AND_RET_HR(pSansBold);

		SDL_Surface* texteSurface = TTF_RenderText_Solid(pSansBold, _Texte.c_str(), color);
		CHK_AND_RET_HR(texteSurface);

		if(_PositionForced)
			_pSurface = SDL_CreateRGBSurface(0, _Position.w, _Position.h, 32, 0, 0, 0, 0);
		else
		{
			int width = pButtonBack->w;
			if (texteSurface->w + 40 > width)
				width = texteSurface->w + 32;
			_pSurface = SDL_CreateRGBSurface(0, width, pButtonBack->h, 32, 0, 0, 0, 0);
		}
		CHK_AND_RET_HR(_pSurface);
		SDL_BlitScaled(pButtonBack, NULL, _pSurface, NULL);
		SDL_FreeSurface(pButtonBack);

		SDL_Rect textePos = { _pSurface->w / 2 - texteSurface->w / 2,
			_pSurface->h / 2 - texteSurface->h / 2, texteSurface->w, texteSurface->h };
		SDL_BlitSurface(texteSurface, NULL, _pSurface, &textePos);
		SDL_FreeSurface(texteSurface);

		TTF_CloseFont(pSansBold);
		pSansBold = NULL;

		break;
	}
	case IMAGE:
	{
		
		if (_Checked)
		{
			SDL_Surface* pButton = IMG_Load(_Image.c_str());

			_pSurface = SDL_CreateRGBSurface(0, pButton->w, pButton->h, 32, 0, 0, 0, 0);
			CHK_AND_RET_HR(_pSurface);

			SDL_FillRect(_pSurface, NULL, SDL_MapRGB(_pSurface->format, 93, 173, 226));
			SDL_BlitSurface(pButton, NULL, _pSurface, NULL);
			SDL_FreeSurface(pButton);
		}
		else
			_pSurface = IMG_Load(_Image.c_str());
		
		CHK_AND_RET_HR(_pSurface);

		break;
	}
	}

	if(!_PositionForced)
		_Position = _pSurface->clip_rect;
	
	return L_S_OK;
}

bool Button::HasBeenClicked(int iX, int iY)
{	
	bool clicked = WindowElement::HasBeenClicked(iX, iY);

	if (_CheckMode && clicked)
	{
		_Checked = !_Checked;
		_Initialized = false;
	}

	return clicked;
}
