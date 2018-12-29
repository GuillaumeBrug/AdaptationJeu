#include "RavenChoiceState.h"
#include "ChoicePrompt.h"
#include "Game.h"
#include "Engine.h"
#include "AssignOrderPrompt.h"
#include "SelectionPrompt.h"

enum CHOICES {
	ORDERSWITCH,
	WILDCARD
};

RavenChoiceState::RavenChoiceState(Game* ipGame):GameState(ipGame), _pChoice(NULL), _pWildCardPrompt(NULL),
_pSelection(NULL), _pAssignPrompt(NULL)
{
}

RavenChoiceState::~RavenChoiceState()
{
	if (NULL != _pChoice)
		delete _pChoice;
	_pChoice = NULL;

	if (NULL != _pWildCardPrompt)
		delete _pWildCardPrompt;
	_pWildCardPrompt = NULL;

	if (NULL != _pSelection)
		delete _pSelection;
	_pSelection = NULL;

	if (NULL != _pAssignPrompt)
		delete _pAssignPrompt;
	_pAssignPrompt = NULL;
}

L_HRESULT RavenChoiceState::Init()
{
	int iWidth = 0, iHeight = 0;
	(_pGame->GetEngine())->GetWindowDimension(iWidth, iHeight);

	_pChoice = new ChoicePrompt(iWidth, iHeight);
	CHK_AND_RET_HR(_pChoice);
	std::vector<std::pair<int, std::string>> choices;
	choices.push_back({ ORDERSWITCH, "Changer Ordre" });
	choices.push_back({ WILDCARD, "Regarder Carte" });
	_pChoice->SetChoices(choices);
	_pChoice->SetText("En tant que possesseur du Corbeau, vous pouvez :");

	_pAssignPrompt = new AssignOrderPrompt(iWidth, iHeight);
	CHK_AND_RET_HR(_pAssignPrompt);

	return L_S_OK;
}

L_HRESULT RavenChoiceState::Activate()
{
	_pCurrentPlayer = _pGame->GetRavenOwner();
	CHK_AND_RET_HR(_pCurrentPlayer);

	_pSelection = new SelectionPrompt(SELECTORDER, _pGame->GetBoard(), _pCurrentPlayer);
	CHK_AND_RET_HR(_pSelection);
	
	_pAssignPrompt->SetGame(_pGame);
	_pAssignPrompt->SetPlayer(_pCurrentPlayer);

	(_pGame->GetEngine())->RegisterPromptWindow(_pChoice);

	_Activated = true;
	return L_S_OK;
}

L_HRESULT RavenChoiceState::Deactivate()
{
	_Activated = false;
	_Completed = false;
	return L_S_OK;
}

L_HRESULT RavenChoiceState::Execute()
{
	if (_pChoice->IsComplete())
	{
		_pChoice->Reset();
		(_pGame->GetEngine())->UnregisterPromptWindow();

		switch (_pChoice->GetChoice())
		{
		case ORDERSWITCH:
		{
			CHK_SUCCESS(_pSelection->Init(_pCurrentPlayer->GetAreasWithUnits()));
			(_pGame->GetEngine())->RegisterSelectionPrompt(_pSelection);
			break;
		}
		case WILDCARD:
			_Completed = true;
			break;
		}
	}

	AREA area = _pSelection->GetSelectedArea();
	if (UNDEFINED_AREA != area)
	{
		_pAssignPrompt->SetArea(area);
		(_pGame->GetEngine())->RegisterPromptWindow(_pAssignPrompt);

		(_pGame->GetEngine())->UnregisterSelectionPrompt();
		_pSelection->Clean();
	}

	if (_pAssignPrompt->IsComplete())
	{
		_pAssignPrompt->Reset();
		(_pGame->GetEngine())->UnregisterPromptWindow();

		ORDER order = _pAssignPrompt->GetSelectedOrder();
		if(UNDEFINED_ORDER != order)
		{
			AREA area = _pAssignPrompt->GetArea();
			if (UNDEFINED_ORDER != order && UNDEFINED_AREA != area)
				CHK_SUCCESS(_pCurrentPlayer->AddOrderInArea(order, area));

			_Completed = true;
		}
		else
		{
			CHK_SUCCESS(_pSelection->Init(_pCurrentPlayer->GetAreasWithUnits()));
			(_pGame->GetEngine())->RegisterSelectionPrompt(_pSelection);
		}
	}

	return L_S_OK;
}