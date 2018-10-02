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

protected:
	WindowPrompt();

	virtual L_HRESULT _OnElementClicked(int iElementID) = 0;

	WindowElement* _ElementExist(int iElementID);

	int _WinWidth;
	int _WinHeight;
	bool _bComplete;
	double _ScaleX;
	double _ScaleY;

	std::vector<WindowElement*> _Elements;
};

