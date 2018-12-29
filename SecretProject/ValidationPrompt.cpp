#include "ValidationPrompt.h"
#include "SDL_TTF.h"
#include "Button.h"

enum Button_ID {
	BUT_OK
};

ValidationPrompt::ValidationPrompt(int iWidth, int iHeight, std::string iText):WindowPrompt(iWidth, iHeight)
{
	_ButtonText = "Validé";
	_Text = iText;
}

ValidationPrompt::~ValidationPrompt()
{
}

L_HRESULT ValidationPrompt::_Init()
{
	SDL_Surface* pBack = IMG_Load("ValidateBack.png");
	CHK_AND_RET_HR(pBack);

	SDL_Surface* pFinalSurface = SDL_CreateRGBSurface(0, pBack->w, pBack->h, 32, 0, 0, 0, 0);
	CHK_AND_RET_HR(pFinalSurface);

	SDL_BlitSurface(pBack, NULL, pFinalSurface, NULL);
	SDL_FreeSurface(pBack);

	SDL_Color color = { 0, 0, 0 };
	TTF_Font* pSansBold = TTF_OpenFont("OpenSans-Bold.ttf", 40);
	CHK_AND_RET_HR(pSansBold);

	SDL_Surface* pTexteSurface = TTF_RenderText_Solid(pSansBold, _Text.c_str(), color);
	CHK_AND_RET_HR(pTexteSurface);

	TTF_CloseFont(pSansBold);
	pSansBold = NULL;

	SDL_Rect position = { 20, pFinalSurface->h / 2 - pTexteSurface->h / 2, pTexteSurface->w, pTexteSurface->h};
	SDL_BlitSurface(pTexteSurface, NULL, pFinalSurface, &position);
	SDL_FreeSurface(pTexteSurface);

	WindowElement* pOKElem = _ElementExist(BUT_OK);
	if (!pOKElem)
	{
		pOKElem = new Button(Button::TEXTE, _ButtonText, BUT_OK);
		_Elements.push_back(pOKElem);
	}
	CHK_AND_RET_HR(pOKElem);

	SDL_Rect pos;
	SDL_Surface* pOKSurface = NULL;
	pOKElem->Render(pOKSurface, pos);
	CHK_AND_RET_HR(pOKSurface);

	SDL_Rect okPos = { pFinalSurface->w - pOKSurface->w - 20, pFinalSurface->h / 2 - pOKSurface->h / 2,
		pOKSurface->w, pOKSurface->h };
	pOKElem->ForcePosition(okPos);

	SDL_BlitSurface(pOKSurface, NULL, pFinalSurface, &okPos);

	_pSurface = SDL_CreateRGBSurface(0, _WinWidth / 3, _WinHeight / 18, 32, 0, 0, 0, 0);
	CHK_AND_RET_HR(_pSurface);

	SDL_BlitScaled(pFinalSurface, NULL, _pSurface, NULL);

	_ScaleX = (double)pFinalSurface->w / (double)_pSurface->w;
	_ScaleY = (double)pFinalSurface->h / (double)_pSurface->h;

	SDL_FreeSurface(pFinalSurface);
	
	_Position = { _WinWidth / 3, _pSurface->h + 15, _WinWidth / 3, _pSurface->h };

	return L_S_OK;
}

L_HRESULT ValidationPrompt::_OnElementClicked(int iElementID)
{
	if (iElementID == BUT_OK)
	{
		_bComplete = true;
		return L_S_OK;
	}
	else
		return L_E_FAIL;
}