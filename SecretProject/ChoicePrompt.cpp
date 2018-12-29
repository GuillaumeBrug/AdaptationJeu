#include "ChoicePrompt.h"
#include "SDL_TTF.h"
#include "Button.h"

ChoicePrompt::ChoicePrompt(int iWinWidth, int iWinHeight):WindowPrompt(iWinWidth, iWinHeight)
{
}

ChoicePrompt::~ChoicePrompt()
{
}

L_HRESULT ChoicePrompt::_Init()
{
	if (_Choices.size() <= 0)
		return L_E_FAIL;
	
	SDL_Surface* pBack = IMG_Load("ChoiceBack.png");
	CHK_AND_RET_HR(pBack);

	SDL_Surface* pFinalSurface = SDL_CreateRGBSurface(0, pBack->w, pBack->h, 32, 0, 0, 0, 0);
	CHK_AND_RET_HR(pFinalSurface);

	SDL_BlitScaled(pBack, NULL, pFinalSurface, NULL);
	SDL_FreeSurface(pBack);

	SDL_Color color = { 0, 0, 0 };
	TTF_Font* pSansBold = TTF_OpenFont("OpenSans-Bold.ttf", 40);
	CHK_AND_RET_HR(pSansBold);

	SDL_Surface* pTexteSurface = TTF_RenderText_Solid(pSansBold, _Text.c_str(), color);
	CHK_AND_RET_HR(pTexteSurface);

	TTF_CloseFont(pSansBold);
	pSansBold = NULL;

	SDL_Rect position = { pFinalSurface->w / 2 - pTexteSurface->w / 2, 
		pFinalSurface->h / 2 - pTexteSurface->h / 2 - 50, 
		pTexteSurface->w, pTexteSurface->h };
	SDL_BlitSurface(pTexteSurface, NULL, pFinalSurface, &position);
	SDL_FreeSurface(pTexteSurface);

	int index = 0;
	std::vector<std::pair<int, std::string>>::iterator it;
	for (it = _Choices.begin(); it != _Choices.end(); it++)
	{
		index++;

		WindowElement* pButtonElem = _ElementExist((*it).first);
		if (!pButtonElem)
		{
			pButtonElem = new Button(Button::TEXTE, (*it).second, (*it).first);
			_Elements.push_back(pButtonElem);
		}
		CHK_AND_RET_HR(pButtonElem);

		SDL_Rect pos;
		SDL_Surface* pButtonSurface = NULL;
		pButtonElem->Render(pButtonSurface, pos);
		CHK_AND_RET_HR(pButtonSurface);

		int x = 0;
		if (_Choices.size() == 1)
		{
			x = 375;
		}
		else if(_Choices.size() == 2)
		{
			if (index == 1)
				x = 125;
			else
				x = 625;
		}
		else
		{
			if (index == 1)
				x = 75;
			else if (index == 2)
				x = 375;
			else
				x = 675;
		}

		SDL_Rect buttonPos = { x, pFinalSurface->h / 2 - pButtonSurface->h / 2 + 50,
			pButtonSurface->w, pButtonSurface->h };
		pButtonElem->ForcePosition(buttonPos);

		SDL_BlitSurface(pButtonSurface, NULL, pFinalSurface, &buttonPos);
	}

	_pSurface = SDL_CreateRGBSurface(0, _WinWidth / 3, _WinHeight / 10, 32, 0, 0, 0, 0);
	CHK_AND_RET_HR(_pSurface);

	SDL_BlitScaled(pFinalSurface, NULL, _pSurface, NULL);

	_ScaleX = (double)pFinalSurface->w / (double)_pSurface->w;
	_ScaleY = (double)pFinalSurface->h / (double)_pSurface->h;

	SDL_FreeSurface(pFinalSurface);

	_Position = { _WinWidth / 3, _WinHeight / 2 - _pSurface->h / 2, _WinWidth / 3, _pSurface->h };

	return L_S_OK;
}

L_HRESULT ChoicePrompt::_OnElementClicked(int iElementID)
{
	_Choice = iElementID;
	_bComplete = true;
	return L_S_OK;
}


