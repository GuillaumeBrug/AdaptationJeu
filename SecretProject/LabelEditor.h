#pragma once
#include "WindowElement.h"
#include <string>

class LabelEditor :
	public WindowElement
{
public:

	enum LABELTYPE {
		EDITOR,
		LABEL
	};

	LabelEditor(LABELTYPE iType, int iID);
	~LabelEditor();

	void SetTexte(std::string iTexte) { _Texte = iTexte; _Initialized = false; }

protected:
	virtual L_HRESULT _Init();

private:
	LABELTYPE _Type;
	std::string _Texte;
};

