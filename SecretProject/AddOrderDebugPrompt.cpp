#include "AddOrderDebugPrompt.h"
#include "Button.h"
#include "LabelEditor.h"
#include "Board.h"
#include "Engine.h"

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
	LAB_ORDER,
	BUT_LEFT_ORDER,
	BUT_RIGHT_ORDER,
	BUT_OK,
	BUT_APPLY,
	BUT_CANCEL
};

AddOrderDebugPrompt::AddOrderDebugPrompt(int iWinWidth, int iWinHeight):WindowPrompt(iWinWidth, iWinHeight),
_NbPlayers(0), _Area(CASTLE_BLACK), _pSelectedPlayer(NULL), _Order(MARCH_MINUS), _pPrompt(NULL), _pEngine(NULL)
{
	_DoDelete = true;
}

AddOrderDebugPrompt::~AddOrderDebugPrompt()
{
	_pSelectedPlayer = NULL;
	_pPrompt = NULL;
	_pEngine = NULL;
}

void AddOrderDebugPrompt::SetPlayer(int iNbPlayers, Player* ipPlayers[6])
{
	_NbPlayers = iNbPlayers;
	for (int i = 0; i < _NbPlayers; i++)
		_pPlayers[i] = ipPlayers[i];
}

L_HRESULT AddOrderDebugPrompt::_Init()
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
		if (!pButtonPlayer)
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

	// Create the Order label
	WindowElement* pOrderElem = _ElementExist(LAB_ORDER);
	if (!pOrderElem)
	{
		pOrderElem = new LabelEditor(LabelEditor::LABEL, LAB_ORDER);
		_Elements.push_back(pOrderElem);
	}
	CHK_AND_RET_HR(pOrderElem);

	LabelEditor* pOrder = (LabelEditor*)pOrderElem;
	CHK_AND_RET_HR(pOrder);
	std::string orderName;
	switch(_Order)
	{
	case MARCH_MINUS:
		orderName = "March -1";
		break;
	case MARCH:
		orderName = "March";
		break;
	case MARCH_STAR:
		orderName = "March +1";
		break;
	case SUPPORT_1:
		orderName = "Support 1";
		break;
	case SUPPORT_2:
		orderName = "Support 2";
		break;
	case SUPPORT_STAR:
		orderName = "Support Star";
		break;
	case DEFENSE_1:
		orderName = "Defense 1";
		break;
	case DEFENSE_2:
		orderName = "Defense 2";
		break;
	case DEFENSE_STAR:
		orderName = "Defense Star";
		break;
	case CONSOLIDATE_1:
		orderName = "Consolidate 1";
		break;
	case CONSOLIDATE_2:
		orderName = "Consolidate 2";
		break;
	case CONSOLIDATE_STAR:
		orderName = "Consolidate Star";
		break;
	case RAID_1:
		orderName = "Raid 1";
		break;
	case RAID_2:
		orderName = "Raid 2";
		break;
	case RAID_STAR:
		orderName = "Raid Star";
		break;
	};
	pOrder->SetTexte(orderName);

	SDL_Rect orderPos = { 200, 460, 550, 100 };
	pOrder->ForcePosition(orderPos);

	SDL_Surface* pOrderSurface = NULL;
	pOrder->Render(pOrderSurface, pos);
	CHK_AND_RET_HR(pOrderSurface);

	SDL_BlitScaled(pOrderSurface, NULL, pFinalSurface, &orderPos);

	// Create the Left Arrow
	WindowElement* pLeftOrderElem = _ElementExist(BUT_LEFT_ORDER);
	if (!pLeftOrderElem)
	{
		pLeftOrderElem = new Button(Button::IMAGE, "ChooseLeft.png", BUT_LEFT_ORDER);
		_Elements.push_back(pLeftOrderElem);
	}
	CHK_AND_RET_HR(pLeftOrderElem);

	SDL_Rect leftOrderPos = { 60, 460, 100 , 100 };
	pLeftOrderElem->ForcePosition(leftOrderPos);

	SDL_Surface* pLeftOrderSurface = NULL;
	pLeftOrderElem->Render(pLeftOrderSurface, pos);
	CHK_AND_RET_HR(pLeftOrderSurface);

	SDL_BlitScaled(pLeftOrderSurface, NULL, pFinalSurface, &leftOrderPos);

	// Create the Right Arrow
	WindowElement* pRightOrderElem = _ElementExist(BUT_RIGHT_ORDER);
	if (!pRightOrderElem)
	{
		pRightOrderElem = new Button(Button::IMAGE, "ChooseRight.png", BUT_RIGHT_ORDER);
		_Elements.push_back(pRightOrderElem);
	}
	CHK_AND_RET_HR(pRightOrderElem);

	SDL_Rect rightOrderPos = { 790, 460, 100 , 100 };
	pRightOrderElem->ForcePosition(rightOrderPos);

	SDL_Surface* pRightOrderSurface = NULL;
	pRightOrderElem->Render(pRightOrderSurface, pos);
	CHK_AND_RET_HR(pRightOrderSurface);

	SDL_BlitScaled(pRightOrderSurface, NULL, pFinalSurface, &rightOrderPos);

	// Create APPLY, CANCEL, OK Buttons
	WindowElement* pApplyElem = _ElementExist(BUT_APPLY);
	if (!pApplyElem)
	{
		pApplyElem = new Button(Button::TEXTE, "Apply", BUT_APPLY);
		_Elements.push_back(pApplyElem);
	}
	CHK_AND_RET_HR(pApplyElem);

	SDL_Rect applyPos = { 60, 660, 250, 80 };
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

L_HRESULT AddOrderDebugPrompt::_OnElementClicked(int iElementID)
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
		break;
	case BUT_RIGHT_AREA:
		_Area = _Area < 57 ? (AREA)(_Area + 1) : (AREA)0;
		break;
	case BUT_LEFT_ORDER:
		_Order = _Order != 0 ? (ORDER)(_Order - 1) : (ORDER)14;
		break;
	case BUT_RIGHT_ORDER:
		_Order = _Order < 14 ? (ORDER)(_Order + 1) : (ORDER)0;
		break;
	case BUT_APPLY:
		CHK_SUCCESS(_Apply());
		break;
	case BUT_OK:
		CHK_SUCCESS(_Apply());
	case BUT_CANCEL:
		_bComplete = true;

		if (_pPrompt && _pEngine)
		{
			_pEngine->UnregisterPromptWindow();
			_pEngine->RegisterPromptWindow(_pPrompt);
		}

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

L_HRESULT AddOrderDebugPrompt::_Apply()
{
	if (NULL == _pSelectedPlayer)
		return L_E_FAIL;

	CHK_SUCCESS(_pSelectedPlayer->AddOrderInArea(_Order, _Area));

	return L_S_OK;
}