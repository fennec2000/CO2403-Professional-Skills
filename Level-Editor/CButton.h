// CButton.h 02/03/2018
// William John Atkin WJAtkin@UCLan.ac.uk
#pragma once
#include "BUILD_ORDER.h"

class CButton : public CHoverUI
{
public:
	CButton(SUIData* pUIData, const char* pButtonText);
	~CButton();

	bool Update() override;

private:
	std::string mButtonTextContext;
	tle::IFont* mpButtonTextFont;
};
