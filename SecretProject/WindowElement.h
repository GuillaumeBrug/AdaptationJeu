#pragma once
#include "GraphicElement.h"
class WindowElement :
	public GraphicElement
{
public:
	~WindowElement();

	int GetID() { return _ID; }

	virtual bool HasBeenClicked(int iX, int iY);

	void ForcePosition(SDL_Rect& iPosition) { _Position = iPosition; _PositionForced = true; }

	bool HasFocusEdit() { return _HasFocusEdit; }

	bool IsActive() { return _Active; }
	void SetActive(bool iActive) { _Active = iActive; }

protected:
	WindowElement(int iID);

	int _ID;
	bool _PositionForced;
	bool _HasFocusEdit;
	bool _Active;
};

