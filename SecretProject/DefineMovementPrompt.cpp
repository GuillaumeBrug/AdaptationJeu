#include "DefineMovementPrompt.h"
#include "SDL_TTF.h"
#include "Board.h"
#include "Button.h"

enum Button_ID {
	BUT_UNIT_1,
	BUT_UNIT_2,
	BUT_UNIT_3,
	BUT_UNIT_4,
	BUT_OK,
	BUT_CANCEL
};

DefineMovementPrompt::DefineMovementPrompt(int iWinWidth, int iWinHeight):WindowPrompt(iWinWidth, iWinHeight)
{
}

DefineMovementPrompt::~DefineMovementPrompt()
{
}

void DefineMovementPrompt::SetUnitsInMove(UNIT iUnit, int iNb)
{
	_unitsInMove.insert(std::pair<UNIT, int>(iUnit, iNb));
}

L_HRESULT DefineMovementPrompt::_Init()
{
	SDL_Surface* pBack = IMG_Load("PromptBack.png");
	CHK_AND_RET_HR(pBack);

	SDL_Surface* pFinalSurface = SDL_CreateRGBSurface(0, pBack->w, pBack->h, 32, 0, 0, 0, 0);
	CHK_AND_RET_HR(pFinalSurface);

	SDL_BlitSurface(pBack, NULL, pFinalSurface, NULL);
	SDL_FreeSurface(pBack);

	SDL_Color color = { 0, 0, 0 };
	TTF_Font* pSansBold = TTF_OpenFont("OpenSans-Bold.ttf", 40);
	CHK_AND_RET_HR(pSansBold);

	SDL_Surface* pTexteSurface = TTF_RenderText_Solid(pSansBold, "Définir marche depuis", color);
	CHK_AND_RET_HR(pTexteSurface);
	SDL_Rect pos = { 25, 20, pTexteSurface->w, pTexteSurface->h };
	SDL_BlitSurface(pTexteSurface, NULL, pFinalSurface, &pos);
	SDL_FreeSurface(pTexteSurface);
	
	pTexteSurface = TTF_RenderText_Solid(pSansBold, Board::GetAreaName(_FromArea).c_str(), color);
	CHK_AND_RET_HR(pTexteSurface);
	pos = { 25, 10 + pTexteSurface->h, pTexteSurface->w, pTexteSurface->h };
	SDL_BlitSurface(pTexteSurface, NULL, pFinalSurface, &pos);
	SDL_FreeSurface(pTexteSurface);

	pTexteSurface = TTF_RenderText_Solid(pSansBold, "Vers", color);
	CHK_AND_RET_HR(pTexteSurface);
	pos = { 25, 2*(10 + pTexteSurface->h), pTexteSurface->w, pTexteSurface->h };
	SDL_BlitSurface(pTexteSurface, NULL, pFinalSurface, &pos);
	SDL_FreeSurface(pTexteSurface);

	pTexteSurface = TTF_RenderText_Solid(pSansBold, Board::GetAreaName(_ToArea).c_str(), color);
	CHK_AND_RET_HR(pTexteSurface);
	pos = { 25, 3*(10 + pTexteSurface->h), pTexteSurface->w, pTexteSurface->h };
	SDL_BlitSurface(pTexteSurface, NULL, pFinalSurface, &pos);
	SDL_FreeSurface(pTexteSurface);

	TTF_CloseFont(pSansBold);
	pSansBold = NULL;

	// Create UNIT Buttons
	std::vector<UNIT> units = _pPlayer->GetUnitsOnArea(_FromArea);
	std::map<UNIT, int> inMove = _unitsInMove;
	std::vector<UNIT>::iterator it;
	int index = 0;
	for (it = units.begin(); it != units.end(); it++)
	{
		index++;

		std::map<UNIT, int>::iterator itInMove = inMove.find((*it));
		if (itInMove != inMove.end() && itInMove->second > 0)
		{
			inMove[(*it)]--;
			continue;
		}

		UNIT unit = (*it);
		Button_ID id;
		if (1 == index) id = BUT_UNIT_1;
		else if (2 == index) id = BUT_UNIT_2;
		else if (3 == index) id = BUT_UNIT_3;
		else id = BUT_UNIT_4;

		WindowElement* pButElem = _ElementExist(id);
		if (!pButElem)
		{
			std::string image;
			switch (unit)
			{
			case FOOTMAN:
				break;
			}

			pButElem = new Button(Button::IMAGE, "", id);
			_Elements.push_back(pButElem);
		}
		CHK_AND_RET_HR(pButElem);
	}

	// Create CANCEL, OK Buttons
	WindowElement* pOKElem = _ElementExist(BUT_OK);
	if (!pOKElem)
	{
		pOKElem = new Button(Button::TEXTE, "OK", BUT_OK);
		_Elements.push_back(pOKElem);
	}
	CHK_AND_RET_HR(pOKElem);

	SDL_Rect okPos = { 350, 660, 250, 80 };
	pOKElem->ForcePosition(okPos);

	SDL_Surface* pOKSurface = NULL;
	pOKElem->Render(pOKSurface, pos);
	CHK_AND_RET_HR(pOKSurface);

	SDL_BlitSurface(pOKSurface, NULL, pFinalSurface, &okPos);

	WindowElement* pCancelElem = _ElementExist(BUT_CANCEL);
	if (!pCancelElem)
	{
		pCancelElem = new Button(Button::TEXTE, "Cancel", BUT_CANCEL);
		_Elements.push_back(pCancelElem);
	}
	CHK_AND_RET_HR(pCancelElem);

	SDL_Rect cancelPos = { 640, 660, 250, 80 };
	pCancelElem->ForcePosition(cancelPos);

	SDL_Surface* pCancelSurface = NULL;
	pCancelElem->Render(pCancelSurface, pos);
	CHK_AND_RET_HR(pCancelSurface);

	SDL_BlitSurface(pCancelSurface, NULL, pFinalSurface, &cancelPos);

	_pSurface = SDL_CreateRGBSurface(0, _WinWidth / 3, _WinHeight / 3, 32, 0, 0, 0, 0);
	CHK_AND_RET_HR(_pSurface);

	SDL_BlitScaled(pFinalSurface, NULL, _pSurface, NULL);

	_ScaleX = (double)pFinalSurface->w / (double)_pSurface->w;
	_ScaleY = (double)pFinalSurface->h / (double)_pSurface->h;

	SDL_FreeSurface(pFinalSurface);

	_Position = { _WinWidth / 2 - _pSurface->w / 2, _WinHeight / 2 - _pSurface->h / 2,
				_pSurface->w , _pSurface->h };

	return L_S_OK;
}

L_HRESULT DefineMovementPrompt::_OnElementClicked(int iElementID)
{
	switch (iElementID)
	{
	case BUT_CANCEL:
	case BUT_OK:
		_bComplete = true;
		break;
	}

	return L_S_OK;
}
