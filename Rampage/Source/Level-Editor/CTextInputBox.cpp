// CTextInputBox.cpp 02/03/2018
// William John Atkin WJAtkin@UCLan.ac.uk
#pragma once
#include "BUILD_ORDER.h"

CTextInputBox::CTextInputBox(SUIData* pUIData, const char* pCursorPath, const char* pHintText) : CHoverUI(pUIData)
{
	// Hint setup
	mHintText = pHintText;
	mpHintFont = mpMyEngine->LoadFont(MP_FONT_FILE_PATH);

	// Cursor setup
	mpCursorSprite = mpMyEngine->CreateSprite(pCursorPath, 0.0f, 0.0f, HIDE_Z_POS);

	// Input font setup
	mpInputFont = mpMyEngine->LoadFont(MP_FONT_FILE_PATH);

	mElementActive = false;
}

CTextInputBox::~CTextInputBox()
{
	// Clean up
	mpMyEngine->RemoveFont(mpHintFont);
	mpMyEngine->RemoveFont(mpInputFont);
	mpMyEngine->RemoveSprite(mpCursorSprite);
}

bool CTextInputBox::Update()
{
	// Test to see if user has clicked the box or if clicked off the element
	// Finds the mouse position on screen
	float mouseX = static_cast<float>(mpMyEngine->GetMouseX());
	float mouseY = static_cast<float>(mpMyEngine->GetMouseY());

	// Test if click was within bounds of box
	if (mouseX >= mMinPos.x && mouseX <= mMaxPos.x)
	{
		if (mouseY >= mMinPos.y && mouseY <= mMaxPos.y)
		{

			ShowHoverSprites();
			if (mpInput->KeyHit(tle::Mouse_LButton))
			{
				mElementActive = true;
			}
		}
		else
		{
			if (mpInput->KeyHit(tle::Mouse_LButton))
			{
				mElementActive = false;
				mpCursorSprite->SetPosition(M_OFFSCREEN_CURSOR_POS.x, M_OFFSCREEN_CURSOR_POS.y);
				mCursorVisable = false;
			}

			ShowNormalSprites();
		}
	}
	else
	{
		if (mpInput->KeyHit(tle::Mouse_LButton))
		{
			mElementActive = false;
			mpCursorSprite->SetPosition(M_OFFSCREEN_CURSOR_POS.x, M_OFFSCREEN_CURSOR_POS.y);
			mCursorVisable = false;
		}

		ShowNormalSprites();
	}

	// Draws the contents of contents to the screen
	mpInputFont->Draw(mContents, static_cast<int>(mMinPos.x), static_cast<int>(mMinPos.y));

	// Update text if the box is active
	if (mElementActive)
	{
		// Updates text in box
		std::vector<tle::EKeyCode> keysHit = mpInput->GetKeysHit();
		for (unsigned int i = 0; i < keysHit.size(); i++)
		{
			//std::cout << keysHit[i]; // For debuging
			if (keysHit[i] == 8)
			{
				// Backspace pressed
				if (mContents.size() > 0)
				{
					mContents.pop_back();
				}
			}
			else if (keysHit[i] == 13)
			{
				// Enter pressed
				mElementActive = false;
				mpCursorSprite->SetPosition(M_OFFSCREEN_CURSOR_POS.x, M_OFFSCREEN_CURSOR_POS.y);
				mCursorVisable = false;
			}
			else if (keysHit[i] == 16)
			{
				// Shift hit
				// Do nothing for now since font is upper
				// case only
			}
			else if (keysHit[i] == 190)
			{
				// . pressed
				// Checks to make sure this wont overflow the
				// text box
				if (mpInputFont->MeasureTextWidth(mContents) + M_MAX_CHAR_SIZE < mMaxPos.x - mMinPos.x)
				{
					mContents += ".";
				}
			}
			else if (keysHit[i] == 220)
			{
				// \ pressed
				mContents += "\\";
			}
			else if (keysHit[i] == 226)
			{
				// \ pressed
				mContents += "\\";
			}
			// Ignored keys
			else if (keysHit[i] == tle::Mouse_LButton || keysHit[i] == tle::Mouse_RButton)
			{

			}
			else
			{
				// Checks to make sure this wont overflow the
				// text box
				if (mpInputFont->MeasureTextWidth(mContents) + M_MAX_CHAR_SIZE < (mMaxPos.x - mMinPos.x))
				{
					mContents += (char)keysHit[i];
				}
			}
		}

		// Tests if the backspace key was held down
		if (mpInput->KeyHeld(tle::Key_Back) && mContents.size() > 0)
		{
			if (mHeldDeleteStarted)
			{
				if (mBackspaceTimer >= M_BACKSPACE_DELETE_SPEED)
				{
					mContents.pop_back();
					mBackspaceTimer = 0.0f;
				}
				mBackspaceTimer += CTime::AdjustedGameTime();
			}
			else
			{
				if (mBackspaceStartTimer >= M_BACKSPACE_START_TIME)
				{
					mHeldDeleteStarted = true;
				}
				else
				{
					mBackspaceStartTimer += CTime::AdjustedGameTime();
				}
			}

		}
		else
		{
			// Resets all of the backspace variables
			mHeldDeleteStarted = false;
			mBackspaceTimer = 0.0f;
			mBackspaceStartTimer = 0.0f;
		}

		// Checks if the hint shoud be displayed
		if (mContents.size() == 0)
		{
			mDisplayHint = true;
		}
		else
		{
			mDisplayHint = false;
		}

		// Cursor blink
		if (mCursorTimer >= M_CURSOR_BLINK_TIME)
		{
			if (mCursorVisable)
			{
				mpCursorSprite->SetZ(HIDE_Z_POS);
				mCursorVisable = false;
			}
			else
			{
				mpCursorSprite->SetPosition(mMinPos.x + mpInputFont->MeasureTextWidth(mContents), mMinPos.y);
				mpCursorSprite->SetZ(0.2f);
				mCursorVisable = true;
			}
			mCursorTimer = 0.0f;
		}
		mCursorTimer += CTime::AdjustedGameTime();
		if (mCursorVisable)
		{
			mpCursorSprite->SetX(mMinPos.x + mpInputFont->MeasureTextWidth(mContents));
		}
	}
	else if (mDisplayHint)
	{
		mpHintFont->Draw(mHintText, static_cast<int>(mMinPos.x), static_cast<int>(mMinPos.y), M_HINT_COLOR);
	}

	return false;
}

std::string CTextInputBox::GetInputedText()
{
	return mContents;
}
