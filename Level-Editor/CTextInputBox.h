// CTextInputBox.h 02/03/2018
// William John Atkin WJAtkin@UCLan.ac.uk
#pragma once
#include "BUILD_ORDER.h"

class CTextInputBox : public CHoverUI
{
public:
	CTextInputBox(SUIData* pUIData, const char* pCursorPath, const char* pHintText);
	~CTextInputBox();

	bool Update() override;

	std::string GetInputedText();

private:

	// Input variables
	std::string mContents;
	tle::IFont* mpInputFont;
	const int M_MAX_CHAR_SIZE = 10;
	
	// Hint variables
	std::string mHintText;
	tle::IFont* mpHintFont;
	const unsigned int M_HINT_COLOR = 0xff808080;
	bool mDisplayHint = true;

	// Backspace variables
	const float M_BACKSPACE_DELETE_SPEED = 0.025f;
	const float M_BACKSPACE_START_TIME = 0.5f;
	float mBackspaceTimer = 0.0f;
	float mBackspaceStartTimer = 0.0f;
	bool mHeldDeleteStarted = false;

	// Cursor variables
	tle::ISprite* mpCursorSprite;
	const float M_CURSOR_BLINK_TIME = 0.5f;
	const SVector2D<float> M_OFFSCREEN_CURSOR_POS = { -100.0f, 0.0f };
	SVector2D<float> mCursorPos;
	float mCursorTimer = 0.0f;
	bool mCursorVisable = false;
};
