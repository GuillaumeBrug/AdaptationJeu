#include "WindowPrompt.h"
#include "WindowElement.h"

WindowPrompt::WindowPrompt(int iWinWidth, int iWinHeight):GraphicElement(), _bComplete(false), 
_ScaleX(0), _ScaleY(0), _WinWidth(iWinWidth), _WinHeight(iWinHeight), _DoDelete(false)
{
}

WindowPrompt::~WindowPrompt()
{
	std::vector<WindowElement*>::iterator it;
	for (it = _Elements.begin(); it != _Elements.end(); it++)
		delete *it;
}

L_HRESULT WindowPrompt::InputClick(int iX, int iY)
{
	// We must translate the input coordinates into the origin reference
	iX = iX * _ScaleX;
	iY = iY * _ScaleY;

	//printf("Click in Prompt at {%d, %d}\n", iX, iY);

	std::vector<WindowElement*>::iterator it;
	for (it = _Elements.begin(); it != _Elements.end(); it++)
	{
		WindowElement* pElement = *it;
		if (NULL == pElement)
			continue;

		if (pElement->HasBeenClicked(iX, iY))
			CHK_SUCCESS(_OnElementClicked(pElement->GetID()));
	}
	return L_S_OK;
}

WindowElement* WindowPrompt::_ElementExist(int iElementID)
{
	std::vector<WindowElement*>::iterator it;
	for (it = _Elements.begin(); it != _Elements.end(); it++)
	{
		WindowElement* pElement = *it;
		if (NULL == pElement)
			continue;

		if (iElementID == pElement->GetID())
			return pElement;
	}
	return NULL;
}
