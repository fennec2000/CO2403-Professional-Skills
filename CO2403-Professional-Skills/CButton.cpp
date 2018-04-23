// CButton.cpp 02/03/2018
// William John Atkin WJAtkin@UCLan.ac.uk
#pragma once
#include "BUILD_ORDER.h"

CButton::CButton(SUIData* pUIData, const char* pButtonText) : CHoverUI(pUIData)
{
	mButtonTextContext = pButtonText;
	mpButtonTextFont = mpMyEngine->LoadFont(MP_FONT_FILE_PATH);
}

CButton::~CButton()
{
	mpMyEngine->RemoveFont(mpButtonTextFont);
}

bool CButton::Update()
{
	mpButtonTextFont->Draw(mButtonTextContext, static_cast<int>(mMinPos.x) + 12, static_cast<int>(mMinPos.y + ((mMaxPos.y - mMinPos.y) / 4.0f))); // Magic numbers...

	// Gets the mouse position
	float mouseX = static_cast<float>(mpMyEngine->GetMouseX());
	float mouseY = static_cast<float>(mpMyEngine->GetMouseY());

	if (mouseX >= mMinPos.x && mouseX <= mMaxPos.x)
	{
		if (mouseY >= mMinPos.y && mouseY <= mMaxPos.y)
		{
			ShowHoverSprites();
			if (mpInput->KeyHit(tle::Mouse_LButton))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	ShowNormalSprites();
	return false;
}