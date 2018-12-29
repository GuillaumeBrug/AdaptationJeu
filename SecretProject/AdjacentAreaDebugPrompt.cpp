#include "AdjacentAreaDebugPrompt.h"
#include "LabelEditor.h"
#include "Board.h"
#include "Button.h"
#include "SelectionPrompt.h"
#include "Tdf_Defs.h"
#include "Engine.h"

enum Button_ID {
	LAB_AREA = 0,
	BUT_LEFT_AREA,
	BUT_RIGHT_AREA,
	BUT_OK
};

AdjacentAreaDebugPrompt::AdjacentAreaDebugPrompt(int iWinWidth, int iWinHeight):WindowPrompt(iWinWidth, iWinHeight),
_Area(CASTLE_BLACK), _pGame(NULL)
{
	_DoDelete = true;
}

AdjacentAreaDebugPrompt::~AdjacentAreaDebugPrompt()
{
	(_pGame->GetEngine())->UnregisterSelectionPrompt();
	delete _pSelection;
	_pSelection = NULL;
}

L_HRESULT AdjacentAreaDebugPrompt::_Init()
{
	SDL_Surface* pBack = IMG_Load("PromptBack.png");
	CHK_AND_RET_HR(pBack);

	SDL_Surface* pFinalSurface = SDL_CreateRGBSurface(0, pBack->w, pBack->h, 32, 0, 0, 0, 0);
	CHK_AND_RET_HR(pFinalSurface);

	SDL_BlitSurface(pBack, NULL, pFinalSurface, NULL);

	// Create the Area label
	WindowElement* pLabelElem = _ElementExist(LAB_AREA);
	if (!pLabelElem)
	{
		pLabelElem = new LabelEditor(LabelEditor::LABEL, LAB_AREA);
		_Elements.push_back(pLabelElem);
	}
	CHK_AND_RET_HR(pLabelElem);

	LabelEditor* pLabel = (LabelEditor*)pLabelElem;
	CHK_AND_RET_HR(pLabel);
	pLabel->SetTexte(Board::GetAreaName(_Area));

	SDL_Rect labelPos = { 200, 320, 550, 100 };
	pLabel->ForcePosition(labelPos);

	SDL_Rect pos;
	SDL_Surface* pLabelSurface = NULL;
	pLabel->Render(pLabelSurface, pos);
	CHK_AND_RET_HR(pLabelSurface);

	SDL_BlitScaled(pLabelSurface, NULL, pFinalSurface, &labelPos);

	// Create the Left Arrow
	WindowElement* pLeftElem = _ElementExist(BUT_LEFT_AREA);
	if (!pLeftElem)
	{
		pLeftElem = new Button(Button::IMAGE, "ChooseLeft.png", BUT_LEFT_AREA);
		_Elements.push_back(pLeftElem);
	}
	CHK_AND_RET_HR(pLeftElem);

	SDL_Rect leftPos = { 60, 320, 100 , 100 };
	pLeftElem->ForcePosition(leftPos);

	SDL_Surface* pLeftSurface = NULL;
	pLeftElem->Render(pLeftSurface, pos);
	CHK_AND_RET_HR(pLeftSurface);

	SDL_BlitScaled(pLeftSurface, NULL, pFinalSurface, &leftPos);

	// Create the Right Arrow
	WindowElement* pRightElem = _ElementExist(BUT_RIGHT_AREA);
	if (!pRightElem)
	{
		pRightElem = new Button(Button::IMAGE, "ChooseRight.png", BUT_RIGHT_AREA);
		_Elements.push_back(pRightElem);
	}
	CHK_AND_RET_HR(pRightElem);

	SDL_Rect rightPos = { 790, 320, 100 , 100 };
	pRightElem->ForcePosition(rightPos);

	SDL_Surface* pRightSurface = NULL;
	pRightElem->Render(pRightSurface, pos);
	CHK_AND_RET_HR(pRightSurface);

	SDL_BlitScaled(pRightSurface, NULL, pFinalSurface, &rightPos);

	WindowElement* pOKElem = _ElementExist(BUT_OK);
	if (!pOKElem)
	{
		pOKElem = new Button(Button::TEXTE, "OK", BUT_OK);
		_Elements.push_back(pOKElem);
	}
	CHK_AND_RET_HR(pOKElem);

	SDL_Rect okPos = { 640, 560, 250, 80 };
	pOKElem->ForcePosition(okPos);

	SDL_Surface* pOKSurface = NULL;
	pOKElem->Render(pOKSurface, pos);
	CHK_AND_RET_HR(pOKSurface);

	SDL_BlitSurface(pOKSurface, NULL, pFinalSurface, &okPos);

	_pSurface = SDL_CreateRGBSurface(0, _WinWidth / 3, _WinHeight / 3, 32, 0, 0, 0, 0);
	CHK_AND_RET_HR(_pSurface);

	SDL_BlitScaled(pFinalSurface, NULL, _pSurface, NULL);

	_ScaleX = (double)pFinalSurface->w / (double)_pSurface->w;
	_ScaleY = (double)pFinalSurface->h / (double)_pSurface->h;

	SDL_FreeSurface(pFinalSurface);

	_Position = { _WinWidth / 2 - _pSurface->w / 2, _WinHeight / 2 - _pSurface->h / 2,
				_pSurface->w , _pSurface->h };

	if(NULL == _pSelection)
		_pSelection = new SelectionPrompt(SELECTORDER, _pGame->GetBoard(), _pGame->GetCurrentPlayer());
	CHK_AND_RET_HR(_pSelection);
	CHK_SUCCESS(_pSelection->Init(Board::GetAdjacentAreas(_Area)));

	return L_S_OK;
}

L_HRESULT AdjacentAreaDebugPrompt::_OnElementClicked(int iElementID)
{
	_Initialized = false; // force to redraw the window

	switch (iElementID)
	{
	case BUT_LEFT_AREA:
		_Area = _Area != 0 ? (AREA)(_Area - 1) : (AREA)57;
		_pSelection->Clean();
		break;
	case BUT_RIGHT_AREA:
		_Area = _Area < 57 ? (AREA)(_Area + 1) : (AREA)0;
		_pSelection->Clean();
		break;
	case BUT_OK:
		_bComplete = true;
		break;
	default:
		break;
	}

	return L_S_OK;
}
