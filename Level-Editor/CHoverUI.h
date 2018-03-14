// CHoverUI.h 02/03/2018
// William John Atkin WJAtkin@UCLan.ac.uk
#pragma once
#include "BUILD_ORDER.h"

class CHoverUI
{
public:
	CHoverUI(SUIData* pUIData);
	~CHoverUI();

	virtual bool Update();
	virtual void DeleteThis();
	virtual void SetEnabled(bool enable);

protected:

	// For switching between displaying hover and normal sprites
	void ShowNormalSprites();
	void ShowHoverSprites();

	// Pointers
	tle::I3DEngine* mpMyEngine;
	std::vector<char*> mSpritePaths;
	std::vector<char*> mHoverSpritePaths;
	const char* MP_FONT_FILE_PATH = "Font1.bmp";
	bool mElementActive = true;
	bool eElementVisable = true;
	
	// Vectors for storing the sprites
	std::vector<tle::ISprite*> mSprites;
	std::vector<tle::ISprite*> mHoverSprites;

	// For storing z positions for swapping the sprite
	// in and out of view of the camera
	float mDefaultZPos = 0.3f;
	const float HIDE_Z_POS = -1.0f;

	// For collision detection
	SVector2D<float> mMinPos;
	SVector2D<float> mMaxPos;

	// Pointer to input for testing mouse click
	CInput* mpInput;
};
