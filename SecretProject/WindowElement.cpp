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
	//printf("Is Element %d  at {%d, %d} sized {%d, %d} clicked ?", _ID, _Position.x, _Position.y, _Position.w, _Position.h);
	
	if (!_Active)
		return false;

	bool inX = iX >= _Position.x && iX <= _Position.x + _Position.w;
	bool inY = iY >= _Position.y && iY <= _Position.y + _Position.h;
	/*if (inX && inY)
		printf(" YES\n");
	else
		printf(" NO\n");*/
	return inX && inY;
}
