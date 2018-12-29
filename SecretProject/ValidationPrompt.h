#pragma once

#include "WindowPrompt.h"

class ValidationPrompt :
	public WindowPrompt
{
public:
	ValidationPrompt(int iWidth, int iHeight, std::string iText);
	~ValidationPrompt();

	void OverrideButtonText(std::string iButText) { _ButtonText = iButText; }

private:
	L_HRESULT _Init();

	L_HRESULT _OnElementClicked(int iElementID);

	std::string _Text;
	std::string _ButtonText;
};

