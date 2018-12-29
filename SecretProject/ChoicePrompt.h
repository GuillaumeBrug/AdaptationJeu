#pragma once

#include "WindowPrompt.h"

class ChoicePrompt :
	public WindowPrompt
{
public:
	ChoicePrompt(int iWinWidth, int iWinHeight);
	~ChoicePrompt();
	   
	void SetText(std::string iText) { _Text = iText; }

	void SetChoices(std::vector<std::pair<int, std::string>> iChoices) { _Choices = iChoices; }
	int GetChoice() { return _Choice; }

private:
	virtual L_HRESULT _Init();

	virtual L_HRESULT _OnElementClicked(int iElementID);

	std::string _Text;
	std::vector<std::pair<int, std::string>> _Choices;
	int _Choice;
};

