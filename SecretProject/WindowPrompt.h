#pragma once

#include "GraphicElement.h"
#include "Tdf_Defs.h"
#include "SDL.h"

class WindowElement;

class WindowPrompt :
	public GraphicElement
{
public:
	virtual ~WindowPrompt();

	L_HRESULT InputClick(int iX, int iY);

	bool IsComplete() { return _bComplete; }
	virtual void Reset() { _bComplete = false; }

	bool DoDelete() { return _DoDelete; }

protected:
	WindowPrompt(int iWinWidth, int iWinHeight);

	virtual L_HRESULT _OnElementClicked(int iElementID) = 0;

	WindowElement* _ElementExist(int iElementID);

	int _WinWidth;
	int _WinHeight;
	bool _bComplete;
	bool _DoDelete;
	double _ScaleX;
	double _ScaleY;

	std::vector<WindowElement*> _Elements;
};

