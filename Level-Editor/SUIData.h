// SUIData.h 02/03/2018
// William John Atkin WJAtkin@UCLan.ac.uk
#pragma once
#include "BUILD_ORDER.h"

struct SUIData
{
	tle::I3DEngine* mpMyEngine;
	CInput* mpInput;
	std::vector<char*> mSpritePaths;
	std::vector<char*> mHoverSpritePaths;
	int mSpriteXSize;
	SVector2D<int> mSize;
	SVector2D<float> mPosition;
};