#include "AddUnitDebugPrompt.h"

#include "SDL_image.h"
#include "SDL_TTF.h"
#include "Player.h"
#include "Button.h"
#include "LabelEditor.h"
#include "Board.h"
#include <string>

enum Button_ID {
	BUT_Player_1 = 0,
	BUT_Player_2,
	BUT_Player_3,
	BUT_Player_4,
	BUT_Player_5,
	BUT_Player_6,
	LAB_AREA,
	BUT_LEFT_AREA,
	BUT_RIGHT_AREA,
	LAB_FOOT,
	BUT_LEFT_FOOT,
	BUT_RIGHT_FOOT,
	LAB_KNI,
	BUT_LEFT_KNI,
	BUT_RIGHT_KNI,
	LAB_ENG,
	BUT_LEFT_ENG,
	BUT_RIGHT_ENG,
	LAB_SHIP,
	BUT_LEFT_SHIP,
	BUT_RIGHT_SHIP,
	BUT_OK,
	BUT_APPLY,
	BUT_CANCEL
};

AddUnitDebugPrompt::AddUnitDebugPrompt(int iWinWidth, int iWinHeight) :WindowPrompt(iWinWidth, iWinHeight),
_NbPlayers(0), _pSelectedPlayer(NULL), _Area(AREA::CASTLE_BLACK), _NbFoot(0), _NbKnight(0),
_NbEngine(0), _NbShip(0)
{
	_DoDelete = true;
}

AddUnitDebugPrompt::~AddUnitDebugPrompt()
{
	_pSelectedPlayer = NULL;
}

L_HRESULT AddUnitDebugPrompt::_Init()
{
	CHK_AND_RET_HR(_pPlayers);

	SDL_Surface* pBack = IMG_Load("PromptBack.png");
	CHK_AND_RET_HR(pBack);
	
	SDL_Surface* pFinalSurface = SDL_CreateRGBSurface(0, pBack->w, pBack->h, 32, 0, 0, 0, 0);
	CHK_AND_RET_HR(pFinalSurface);

	SDL_BlitSurface(pBack, NULL, pFinalSurface, NULL);

	// Create the Players Buttons
	for (int i = 0; i < _NbPlayers; i++)
	{
		std::string name = (_pPlayers[i])->GetName();
		
		Button* pButtonPlayer = NULL;
		WindowElement* pButtonElem = _ElementExist(i);
		if (!pButtonElem)
		{
			pButtonElem = new Button(Button::TEXTE, name, i);
			pButtonPlayer = (Button*)pButtonElem;
			CHK_AND_RET_HR(pButtonPlayer);

			pButtonPlayer->SetCheckMode(true);
			_Buttons.push_back(pButtonPlayer);
			_Elements.push_back(pButtonElem);
		}
		if(!pButtonPlayer)
		{
			pButtonPlayer = (Button*)pButtonElem;
			CHK_AND_RET_HR(pButtonPlayer);
		}

		SDL_Rect pos = { 0, 0, 250, 80 };
		if (0 == i)
		{ 
			pos.x = 60; pos.y = 80; 
		}
		else if (1 == i)
		{ 
			pos.x = 350; pos.y = 80; 
		}
		else if (2 == i)
		{ 
			pos.x = 640; pos.y = 80; 
		}
		else if (3 == i)
		{
			pos.x = 60; pos.y = 200;
		}
		else if (4 == i)
		{
			pos.x = 350; pos.y = 200;
		}
		else if (5 == i)
		{
			pos.x = 640; pos.y = 200;
		}

		SDL_Surface* pButtonSurface = NULL;
		SDL_Rect position;
		pButtonPlayer->ForcePosition(pos);
		pButtonPlayer->Render(pButtonSurface, position);
		CHK_AND_RET_HR(pButtonSurface);

		SDL_BlitSurface(pButtonSurface, NULL, pFinalSurface, &pos);
	}

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

	// Create the Units Number selection
	SDL_Color color = { 0, 0, 0 };
	TTF_Font* pSansBold = TTF_OpenFont("OpenSans-Bold.ttf", 40);
	CHK_AND_RET_HR(pSansBold);

	if (Board::IsAreaASea(_Area) || Board::IsAreaAPort(_Area))
	{
		SDL_Surface* pShipSurface = TTF_RenderText_Solid(pSansBold, "Ship", color);
		CHK_AND_RET_HR(pShipSurface);
		pos = { 60, 460, pShipSurface->w, pShipSurface->h };
		SDL_BlitScaled(pShipSurface, NULL, pFinalSurface, &pos);

		// Deactivate other elements
		WindowElement* pElem = _ElementExist(BUT_LEFT_FOOT);
		if (pElem)
			pElem->SetActive(false);
		pElem = _ElementExist(BUT_RIGHT_FOOT);
		if (pElem)
			pElem->SetActive(false);
		pElem = _ElementExist(BUT_LEFT_KNI);
		if (pElem)
			pElem->SetActive(false);
		pElem = _ElementExist(BUT_RIGHT_KNI);
		if (pElem)
			pElem->SetActive(false);
		pElem = _ElementExist(BUT_LEFT_ENG);
		if (pElem)
			pElem->SetActive(false);
		pElem = _ElementExist(BUT_RIGHT_ENG);
		if (pElem)
			pElem->SetActive(false);

		// Create the Left Arrow
		WindowElement* pLeftShipElem = _ElementExist(BUT_LEFT_SHIP);
		if (!pLeftShipElem)
		{
			pLeftShipElem = new Button(Button::IMAGE, "ChooseLeft.png", BUT_LEFT_SHIP);
			_Elements.push_back(pLeftShipElem);
		}
		CHK_AND_RET_HR(pLeftShipElem);
		pLeftShipElem->SetActive(true);

		SDL_Rect leftShiptPos = { 210, 460, 80 , 80 };
		pLeftShipElem->ForcePosition(leftShiptPos);

		SDL_Surface* pLeftShipSurface = NULL;
		pLeftShipElem->Render(pLeftShipSurface, pos);
		CHK_AND_RET_HR(pLeftShipSurface);

		SDL_BlitScaled(pLeftShipSurface, NULL, pFinalSurface, &leftShiptPos);

		// Create integer Label
		WindowElement* pLabelShipElem = _ElementExist(LAB_SHIP);
		if (!pLabelShipElem)
		{
			pLabelShipElem = new LabelEditor(LabelEditor::LABEL, LAB_SHIP);
			_Elements.push_back(pLabelShipElem);
		}
		CHK_AND_RET_HR(pLabelShipElem);

		LabelEditor* pLabelShip = (LabelEditor*)pLabelShipElem;
		CHK_AND_RET_HR(pLabelShip);
		pLabelShip->SetTexte(std::to_string(_NbShip));

		SDL_Rect labelShipPos = { 300, 460, 100, 80 };
		pLabelShip->ForcePosition(labelShipPos);

		SDL_Rect pos;
		SDL_Surface* pLabelShipSurface = NULL;
		pLabelShip->Render(pLabelShipSurface, pos);
		CHK_AND_RET_HR(pLabelShipSurface);

		SDL_BlitScaled(pLabelShipSurface, NULL, pFinalSurface, &labelShipPos);

		// Create the Right Arrow
		WindowElement* pRightShipElem = _ElementExist(BUT_RIGHT_SHIP);
		if (!pRightShipElem)
		{
			pRightShipElem = new Button(Button::IMAGE, "ChooseRight.png", BUT_RIGHT_SHIP);
			_Elements.push_back(pRightShipElem);
		}
		CHK_AND_RET_HR(pRightShipElem);
		pRightShipElem->SetActive(true);

		SDL_Rect rightShiptPos = { 420, 460, 80 , 80 };
		pRightShipElem->ForcePosition(rightShiptPos);

		SDL_Surface* pRightShipSurface = NULL;
		pRightShipElem->Render(pRightShipSurface, pos);
		CHK_AND_RET_HR(pRightShipSurface);

		SDL_BlitScaled(pRightShipSurface, NULL, pFinalSurface, &rightShiptPos);
	}
	else
	{
		// Deactivate other elements
		WindowElement* pElem = _ElementExist(BUT_LEFT_SHIP);
		if (pElem)
			pElem->SetActive(false);
		pElem = _ElementExist(BUT_RIGHT_SHIP);
		if (pElem)
			pElem->SetActive(false);

		SDL_Surface* pFootSurface = TTF_RenderText_Solid(pSansBold, "Footman", color);
		CHK_AND_RET_HR(pFootSurface);
		pos = { 60, 460, pFootSurface->w, pFootSurface->h };
		SDL_BlitScaled(pFootSurface, NULL, pFinalSurface, &pos);

		// Create the Left Arrow
		WindowElement* pLeftFootElem = _ElementExist(BUT_LEFT_FOOT);
		if (!pLeftFootElem)
		{
			pLeftFootElem = new Button(Button::IMAGE, "ChooseLeft.png", BUT_LEFT_FOOT);
			_Elements.push_back(pLeftFootElem);
		}
		CHK_AND_RET_HR(pLeftFootElem);
		pLeftFootElem->SetActive(true);

		SDL_Rect leftFoottPos = { 250, 460, 60 , 60 };
		pLeftFootElem->ForcePosition(leftFoottPos);

		SDL_Surface* pLeftFootSurface = NULL;
		pLeftFootElem->Render(pLeftFootSurface, pos);
		CHK_AND_RET_HR(pLeftFootSurface);

		SDL_BlitScaled(pLeftFootSurface, NULL, pFinalSurface, &leftFoottPos);

		// Create integer Label
		WindowElement* pLabelFootElem = _ElementExist(LAB_FOOT);
		if (!pLabelFootElem)
		{
			pLabelFootElem = new LabelEditor(LabelEditor::LABEL, LAB_FOOT);
			_Elements.push_back(pLabelFootElem);
		}
		CHK_AND_RET_HR(pLabelFootElem);

		LabelEditor* pLabelFoot = (LabelEditor*)pLabelFootElem;
		CHK_AND_RET_HR(pLabelFoot);
		pLabelFoot->SetTexte(std::to_string(_NbFoot));

		SDL_Rect labelFootPos = { 320, 460, 100, 60 };
		pLabelFoot->ForcePosition(labelFootPos);

		SDL_Rect pos;
		SDL_Surface* pLabelFootSurface = NULL;
		pLabelFoot->Render(pLabelFootSurface, pos);
		CHK_AND_RET_HR(pLabelFootSurface);

		SDL_BlitScaled(pLabelFootSurface, NULL, pFinalSurface, &labelFootPos);

		// Create the Right Arrow
		WindowElement* pRightFootElem = _ElementExist(BUT_RIGHT_FOOT);
		if (!pRightFootElem)
		{
			pRightFootElem = new Button(Button::IMAGE, "ChooseRight.png", BUT_RIGHT_FOOT);
			_Elements.push_back(pRightFootElem);
		}
		CHK_AND_RET_HR(pRightFootElem);
		pRightFootElem->SetActive(true);

		SDL_Rect rightFoottPos = { 430, 460, 60 , 60 };
		pRightFootElem->ForcePosition(rightFoottPos);

		SDL_Surface* pRightFootSurface = NULL;
		pRightFootElem->Render(pRightFootSurface, pos);
		CHK_AND_RET_HR(pRightFootSurface);

		SDL_BlitScaled(pRightFootSurface, NULL, pFinalSurface, &rightFoottPos);

		SDL_Surface* pKnightSurface = TTF_RenderText_Solid(pSansBold, "Knight", color);
		CHK_AND_RET_HR(pKnightSurface);
		pos = { 60, 540, pKnightSurface->w, pKnightSurface->h };
		SDL_BlitScaled(pKnightSurface, NULL, pFinalSurface, &pos);

		// Create the Left Arrow
		WindowElement* pLeftKnightElem = _ElementExist(BUT_LEFT_KNI);
		if (!pLeftKnightElem)
		{
			pLeftKnightElem = new Button(Button::IMAGE, "ChooseLeft.png", BUT_LEFT_KNI);
			_Elements.push_back(pLeftKnightElem);
		}
		CHK_AND_RET_HR(pLeftKnightElem);
		pLeftKnightElem->SetActive(true);

		SDL_Rect leftKnighttPos = { 250, 540, 60 , 60 };
		pLeftKnightElem->ForcePosition(leftKnighttPos);

		SDL_Surface* pLeftKnightSurface = NULL;
		pLeftKnightElem->Render(pLeftKnightSurface, pos);
		CHK_AND_RET_HR(pLeftKnightSurface);

		SDL_BlitScaled(pLeftKnightSurface, NULL, pFinalSurface, &leftKnighttPos);

		// Create integer Label
		WindowElement* pLabelKnightElem = _ElementExist(LAB_KNI);
		if (!pLabelKnightElem)
		{
			pLabelKnightElem = new LabelEditor(LabelEditor::LABEL, LAB_KNI);
			_Elements.push_back(pLabelKnightElem);
		}
		CHK_AND_RET_HR(pLabelKnightElem);

		LabelEditor* pLabelKnight = (LabelEditor*)pLabelKnightElem;
		CHK_AND_RET_HR(pLabelKnight);
		pLabelKnight->SetTexte(std::to_string(_NbKnight));

		SDL_Rect labelKnightPos = { 320, 540, 100, 60 };
		pLabelKnight->ForcePosition(labelKnightPos);

		SDL_Surface* pLabelKnightSurface = NULL;
		pLabelKnight->Render(pLabelKnightSurface, pos);
		CHK_AND_RET_HR(pLabelKnightSurface);

		SDL_BlitScaled(pLabelKnightSurface, NULL, pFinalSurface, &labelKnightPos);

		// Create the Right Arrow
		WindowElement* pRightKnightElem = _ElementExist(BUT_RIGHT_KNI);
		if (!pRightKnightElem)
		{
			pRightKnightElem = new Button(Button::IMAGE, "ChooseRight.png", BUT_RIGHT_KNI);
			_Elements.push_back(pRightKnightElem);
		}
		CHK_AND_RET_HR(pRightKnightElem);
		pRightKnightElem->SetActive(true);

		SDL_Rect rightKnighttPos = { 430, 540, 60 , 60 };
		pRightKnightElem->ForcePosition(rightKnighttPos);

		SDL_Surface* pRightKnightSurface = NULL;
		pRightKnightElem->Render(pRightKnightSurface, pos);
		CHK_AND_RET_HR(pRightKnightSurface);

		SDL_BlitScaled(pRightKnightSurface, NULL, pFinalSurface, &rightKnighttPos);

		SDL_Surface* pEngineSurface = TTF_RenderText_Solid(pSansBold, "Engine", color);
		CHK_AND_RET_HR(pEngineSurface);
		pos = { 60, 620, pEngineSurface->w, pEngineSurface->h };
		SDL_BlitScaled(pEngineSurface, NULL, pFinalSurface, &pos);

		// Create the Left Arrow
		WindowElement* pLeftEngineElem = _ElementExist(BUT_LEFT_ENG);
		if (!pLeftEngineElem)
		{
			pLeftEngineElem = new Button(Button::IMAGE, "ChooseLeft.png", BUT_LEFT_ENG);
			_Elements.push_back(pLeftEngineElem);
		}
		CHK_AND_RET_HR(pLeftEngineElem);
		pLeftEngineElem->SetActive(true);

		SDL_Rect leftEnginePos = { 250, 620, 60 , 60 };
		pLeftEngineElem->ForcePosition(leftEnginePos);

		SDL_Surface* pLeftEngineSurface = NULL;
		pLeftEngineElem->Render(pLeftEngineSurface, pos);
		CHK_AND_RET_HR(pLeftEngineSurface);

		SDL_BlitScaled(pLeftEngineSurface, NULL, pFinalSurface, &leftEnginePos);

		// Create integer Label
		WindowElement* pLabelEngineElem = _ElementExist(LAB_ENG);
		if (!pLabelEngineElem)
		{
			pLabelEngineElem = new LabelEditor(LabelEditor::LABEL, LAB_ENG);
			_Elements.push_back(pLabelEngineElem);
		}
		CHK_AND_RET_HR(pLabelEngineElem);

		LabelEditor* pLabelEngine = (LabelEditor*)pLabelEngineElem;
		CHK_AND_RET_HR(pLabelEngine);
		pLabelEngine->SetTexte(std::to_string(_NbEngine));

		SDL_Rect labelEnginePos = { 320, 620, 100, 60 };
		pLabelEngine->ForcePosition(labelEnginePos);

		SDL_Surface* pLabelEngineSurface = NULL;
		pLabelEngine->Render(pLabelEngineSurface, pos);
		CHK_AND_RET_HR(pLabelEngineSurface);

		SDL_BlitScaled(pLabelEngineSurface, NULL, pFinalSurface, &labelEnginePos);

		// Create the Right Arrow
		WindowElement* pRightEngineElem = _ElementExist(BUT_RIGHT_ENG);
		if (!pRightEngineElem)
		{
			pRightEngineElem = new Button(Button::IMAGE, "ChooseRight.png", BUT_RIGHT_ENG);
			_Elements.push_back(pRightEngineElem);
		}
		CHK_AND_RET_HR(pRightEngineElem);
		pRightEngineElem->SetActive(true);

		SDL_Rect rightEnginetPos = { 430, 620, 60 , 60 };
		pRightEngineElem->ForcePosition(rightEnginetPos);

		SDL_Surface* pRightEngineSurface = NULL;
		pRightEngineElem->Render(pRightEngineSurface, pos);
		CHK_AND_RET_HR(pRightEngineSurface);

		SDL_BlitScaled(pRightEngineSurface, NULL, pFinalSurface, &rightEnginetPos);
	}

	// Create APPLY, CANCEL, OK Buttons
	WindowElement* pApplyElem = _ElementExist(BUT_APPLY);
	if (!pApplyElem)
	{
		pApplyElem = new Button(Button::TEXTE, "Apply", BUT_APPLY);
		_Elements.push_back(pApplyElem);
	}
	CHK_AND_RET_HR(pApplyElem);

	SDL_Rect applyPos = { 640, 460, 250, 80 };
	pApplyElem->ForcePosition(applyPos);

	SDL_Surface* pApplySurface = NULL;
	pApplyElem->Render(pApplySurface, pos);
	CHK_AND_RET_HR(pApplySurface);

	SDL_BlitSurface(pApplySurface, NULL, pFinalSurface, &applyPos);

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

	TTF_CloseFont(pSansBold);
	pSansBold = NULL;

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

L_HRESULT AddUnitDebugPrompt::_OnElementClicked(int iElementID)
{	
	_Initialized = false; // force to redraw the window
		
	bool buttonCliked = false;
	switch (iElementID)
	{
	case BUT_Player_1:
		_pSelectedPlayer = _pSelectedPlayer != _pPlayers[0] ? _pPlayers[0] : NULL;
		buttonCliked = true;
		break;
	case BUT_Player_2:
		_pSelectedPlayer = _pSelectedPlayer != _pPlayers[1] ? _pPlayers[1] : NULL;
		buttonCliked = true;
		break;
	case BUT_Player_3:
		_pSelectedPlayer = _pSelectedPlayer != _pPlayers[2] ? _pPlayers[2] : NULL;
		buttonCliked = true;
		break;
	case BUT_Player_4:
		_pSelectedPlayer = _pSelectedPlayer != _pPlayers[3] ? _pPlayers[3] : NULL;
		buttonCliked = true;
		break;
	case BUT_Player_5:
		_pSelectedPlayer = _pSelectedPlayer != _pPlayers[4] ? _pPlayers[4] : NULL;
		buttonCliked = true;
		break;
	case BUT_Player_6:
		_pSelectedPlayer = _pSelectedPlayer != _pPlayers[5] ? _pPlayers[5] : NULL;
		buttonCliked = true;
		break;
	case BUT_LEFT_AREA:
		_Area = _Area != 0 ? (AREA)(_Area - 1) : (AREA)57;
		CHK_SUCCESS(_UpdateUnitsForCurrentAreaAndPlayer());
		break;
	case BUT_RIGHT_AREA:
		_Area = _Area < 57? (AREA)(_Area + 1) : (AREA)0;
		CHK_SUCCESS(_UpdateUnitsForCurrentAreaAndPlayer());
		break;
	case BUT_LEFT_FOOT:
		_NbFoot = _NbFoot > 0 ? _NbFoot - 1 : _NbFoot;
		break;
	case BUT_RIGHT_FOOT:
		_NbFoot = _NbFoot  + _NbKnight + _NbEngine < 4 ? _NbFoot + 1 : _NbFoot;
		break;
	case BUT_LEFT_KNI:
		_NbKnight = _NbKnight > 0 ? _NbKnight - 1 : _NbKnight;
		break;
	case BUT_RIGHT_KNI:
		_NbKnight = _NbFoot + _NbKnight + _NbEngine < 4 ? _NbKnight + 1 : _NbKnight;
		break;
	case BUT_LEFT_ENG:
		_NbEngine = _NbEngine > 0 ? _NbEngine - 1 : _NbEngine;
		break;
	case BUT_RIGHT_ENG:
		_NbEngine = _NbFoot + _NbKnight + _NbEngine < 4 ? _NbEngine + 1 : _NbEngine;
		break;
	case BUT_LEFT_SHIP:
		_NbShip = _NbShip > 0 ? _NbShip - 1 : _NbShip;
		break;
	case BUT_RIGHT_SHIP:
		_NbShip = _NbShip < 4 ? _NbShip + 1 : _NbShip;
		break;
	case BUT_APPLY:
		CHK_SUCCESS(_Apply());
		break;
	case BUT_OK:
		CHK_SUCCESS(_Apply());
	case BUT_CANCEL:
		_bComplete = true;
		break;
	default:
		break;
	}

	if (buttonCliked)
	{
		std::vector<Button*>::iterator it;
		for (it = _Buttons.begin(); it != _Buttons.end(); it++)
		{
			Button* pButton = (*it);
			if (NULL == pButton)
				continue;

			if (iElementID != pButton->GetID())
				pButton->SetCheckState(false);
		}
	}

	return L_S_OK;
}

void AddUnitDebugPrompt::SetPlayer(int iNbPlayers, Player* ipPlayers[6])
{
	_NbPlayers = iNbPlayers;
	for (int i = 0; i < _NbPlayers; i++)
		_pPlayers[i] = ipPlayers[i];
}

L_HRESULT AddUnitDebugPrompt::_Apply()
{
	if (NULL == _pSelectedPlayer)
		return L_E_FAIL;

	CHK_SUCCESS(_pSelectedPlayer->_RemoveAllUnitsFromArea(_Area));

	for(int i = 1; i <= _NbFoot; i++)
		CHK_SUCCESS(_pSelectedPlayer->_AddUnitInArea(UNIT::FOOTMAN, _Area));

	for (int i = 1; i <= _NbKnight; i++)
		CHK_SUCCESS(_pSelectedPlayer->_AddUnitInArea(UNIT::KNIGHT, _Area));

	for (int i = 1; i <= _NbEngine; i++)
		CHK_SUCCESS(_pSelectedPlayer->_AddUnitInArea(UNIT::ENGINE, _Area));

	for (int i = 1; i <= _NbShip; i++)
		CHK_SUCCESS(_pSelectedPlayer->_AddUnitInArea(UNIT::SHIP, _Area));

	return L_S_OK;
}

L_HRESULT AddUnitDebugPrompt::_UpdateUnitsForCurrentAreaAndPlayer()
{
	_NbShip = 0;
	_NbFoot = 0;
	_NbKnight = 0;
	_NbEngine = 0;

	if (!_pSelectedPlayer)
		return L_S_OK;
		
	std::map<int, std::vector<int>>::iterator it = (_pSelectedPlayer->_DeployedUnits).find(_Area);
	if(it == (_pSelectedPlayer->_DeployedUnits).end())
		return L_S_OK;

	std::vector<int>::iterator itUnit;
	for (itUnit = (it->second).begin(); itUnit != (it->second).end(); itUnit++)
	{
		int unit = (*itUnit);
		switch ((UNIT)unit)
		{
		case SHIP:
			_NbShip++;
			break;
		case FOOTMAN:
			_NbFoot++;
			break;
		case KNIGHT:
			_NbKnight++;
			break;
		case ENGINE:
			_NbEngine++;
			break;
		}
	}

	return L_S_OK;
}
