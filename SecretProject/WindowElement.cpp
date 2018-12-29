#include "WindowElement.h"

WindowElement::WindowElement(int iID):GraphicElement(), _ID(iID), _PositionForced(false),
_HasFocusEdit(false), _Active(true)
{
}


WindowElement::~WindowElement()
{
}

bool WindowElement::HasBeenClicked(int iX, int iY)
{
	if (!_Active)
		return false;

	return GraphicElement::HasBeenClicked(iX, iY);
}
