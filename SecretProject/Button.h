#pragma once

#include "WindowElement.h"
#include "Tdf_Defs.h"
#include "SDL.h"
#include <string>

class Button :
	public WindowElement
{
public:

	enum BUTTONTYPE {
		TEXTE,
		IMAGE
	};

	Button(BUTTONTYPE iType, std::string iTexteOrName, int iID);
	~Button();
	
	void SetCheckMode(bool iMode) { _CheckMode = iMode; }
	bool GetCheckState() { return _Checked; }
	void SetCheckState(bool iCheckState);

	virtual bool HasBeenClicked(int iX, int iY);

protected:
	L_HRESULT _Init();

private:
	BUTTONTYPE _eType;
	std::string _Texte;
	std::string _Image;
	int _ID;
	bool _CheckMode;
	bool _Checked;
};

