#include "AssignOrderPrompt.h"
#include "Button.h"
#include "WindowElement.h"
#include "Game.h"

enum Button_ID {
	BUT_MARCHMINUS = 0,
	BUT_MARCH,
	BUT_MARCHPLUS,
	BUT_SUPPORT1,
	BUT_SUPPORT2,
	BUT_SUPPORTSTAR,
	BUT_DEFENSE1,
	BUT_DEFENSE2,
	BUT_DEFENSESTAR,
	BUT_CONSOLIDATE1,
	BUT_CONSOLIDATE2,
	BUT_CONSOLIDATESTAR,
	BUT_RAID1,
	BUT_RAID2,
	BUT_RAIDSTAR,
	BUT_OK,
	BUT_CANCEL
};

AssignOrderPrompt::AssignOrderPrompt(int iWidth, int iHeight):WindowPrompt(iWidth, iHeight),
_pPlayer(NULL), _Area(UNDEFINED_AREA), _pGame(NULL), _SelectedOrder(UNDEFINED_ORDER)
{
}

AssignOrderPrompt::~AssignOrderPrompt()
{
	_pGame = NULL;
	_pPlayer = NULL;
}

L_HRESULT AssignOrderPrompt::_Init()
{
	CHK_AND_RET_HR(_pGame);
	CHK_AND_RET_HR(_pPlayer);
	if (_Area == UNDEFINED_AREA)
		return L_E_FAIL;

	SDL_Surface* pBack = IMG_Load("PromptBack.png");
	CHK_AND_RET_HR(pBack);

	SDL_Surface* pFinalSurface = SDL_CreateRGBSurface(0, pBack->w, pBack->h, 32, 0, 0, 0, 0);
	CHK_AND_RET_HR(pFinalSurface);

	SDL_BlitSurface(pBack, NULL, pFinalSurface, NULL);

	std::vector<ORDER> availableOrders = _pGame->GetAvailableOrder(_pPlayer);
	std::vector<ORDER> plannedOrders = _pPlayer->GetPlannedOrders();
	
	// Create Order's Buttons
	std::vector<ORDER>::iterator it;
	int index = 0;
	for (it = availableOrders.begin(); it != availableOrders.end(); it++)
	{
		index++;
		WindowElement* pOrderElem = _ElementExist(*it);
		if (!pOrderElem)
		{
			std::string imageName;
			switch ((ORDER)*it)
			{
			case MARCH_MINUS:
				imageName = "MarchMinusOrder.png";
				break;
			case MARCH:
				imageName = "MarchOrder.png";
				break;
			case MARCH_STAR:
				imageName = "MarchPlusOrder.png";
				break;
			case SUPPORT_1:
			case SUPPORT_2:
				imageName = "SupportOrder.png";
				break;
			case SUPPORT_STAR:
				imageName = "SupportStarOrder.png";
				break;
			case DEFENSE_1:
			case DEFENSE_2:
				imageName = "DefenseOrder.png";
				break;
			case DEFENSE_STAR:
				imageName = "DefensePlusOrder.png";
				break;
			case CONSOLIDATE_1:
			case CONSOLIDATE_2:
				imageName = "ConsolidateOrder.png";
				break;
			case CONSOLIDATE_STAR:
				imageName = "ConsolidateStarOrder.png";
				break;
			case RAID_1:
			case RAID_2:
				imageName = "RaidOrder.png";
				break;
			case RAID_STAR:
				imageName = "RaidStarOrder.png";
				break;
			}
			pOrderElem = new Button(Button::IMAGE, imageName, *it);
			_Elements.push_back(pOrderElem);
		}
		CHK_AND_RET_HR(pOrderElem);

		SDL_Rect orderPos = { 0, 0, 160, 160 };
		if (1 == index)
		{
			orderPos.x = 40; 
			orderPos.y = 40;
		}
		else if(2 == index)
		{
			orderPos.x = 220;
			orderPos.y = 40;
		}
		else if (3 == index)
		{
			orderPos.x = 400;
			orderPos.y = 40;
		}
		else if (4 == index)
		{
			orderPos.x = 580;
			orderPos.y = 40;
		}
		else if (5 == index)
		{
			orderPos.x = 760;
			orderPos.y = 40;
		}
		else if (6 == index)
		{
			orderPos.x = 40;
			orderPos.y = 240;
		}
		else if (7 == index)
		{
			orderPos.x = 220;
			orderPos.y = 240;
		}
		else if (8 == index)
		{
			orderPos.x = 400;
			orderPos.y = 240;
		}
		else if (9 == index)
		{
			orderPos.x = 580;
			orderPos.y = 240;
		}
		else if (10 == index)
		{
			orderPos.x = 760;
			orderPos.y = 240;
		}
		else if (11 == index)
		{
			orderPos.x = 40;
			orderPos.y = 440;
		}
		else if (12 == index)
		{
			orderPos.x = 220;
			orderPos.y = 440;
		}
		else if (13 == index)
		{
			orderPos.x = 400;
			orderPos.y = 440;
		}
		else if (14 == index)
		{
			orderPos.x = 580;
			orderPos.y = 440;
		}
		else if (15 == index)
		{
			orderPos.x = 760;
			orderPos.y = 440;
		}

		pOrderElem->ForcePosition(orderPos);

		SDL_Surface* pOrderSurface = NULL;
		SDL_Rect pos;
		pOrderElem->Render(pOrderSurface, pos);
		CHK_AND_RET_HR(pOrderSurface);

		std::vector<ORDER>::iterator itPlanned = std::find(plannedOrders.begin(), plannedOrders.end(), (*it));
		if (itPlanned != plannedOrders.end())
		{
			SDL_Surface* pBack = SDL_CreateRGBSurface(0, 176, 176, 32, 0, 0, 0, 0);
			CHK_AND_RET_HR(pBack);
			SDL_FillRect(pBack, NULL, SDL_MapRGB(pBack->format, 0, 0, 0));

			SDL_Rect fillRect = {8, 8, 160, 160};
			SDL_FillRect(pBack, &fillRect, SDL_MapRGB(pBack->format, 255, 255, 255));

			SDL_Rect backPos = { orderPos.x - 8, orderPos.y - 8, 176, 176 };
			SDL_BlitScaled(pBack, NULL, pFinalSurface, &backPos);
			SDL_FreeSurface(pBack);
		}

		SDL_BlitScaled(pOrderSurface, NULL, pFinalSurface, &orderPos);
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
	SDL_Rect pos;
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

L_HRESULT AssignOrderPrompt::_OnElementClicked(int iElementID)
{
	_Initialized = false; // force to redraw the window

	bool buttonCliked = false;
	if (iElementID < BUT_OK)
	{
		_SelectedOrder = (ORDER)iElementID;
		WindowElement* pElement = _ElementExist(iElementID);
		CHK_AND_RET_HR(pElement);
		Button* pButton = (Button*)pElement;
		CHK_AND_RET_HR(pButton);
		pButton->SetCheckState(true);
		buttonCliked = true;
	}
	else
	{
		switch (iElementID)
		{
		case BUT_CANCEL:
			_SelectedOrder = UNDEFINED_ORDER;
		case BUT_OK:
			_bComplete = true;
			break;
		}
	}
	
	if (buttonCliked)
	{
		std::vector<WindowElement*>::iterator it;
		for (it = _Elements.begin(); it != _Elements.end(); it++)
		{
			Button* pButton = (Button*) (*it);
			if (NULL == pButton)
				continue;

			if (iElementID != pButton->GetID())
				pButton->SetCheckState(false);

			if (iElementID >= BUT_OK)
				break;
		}
	}

	return L_S_OK;
}

void AssignOrderPrompt::Reset()
{
	_Initialized = false;
	WindowPrompt::Reset();
}
