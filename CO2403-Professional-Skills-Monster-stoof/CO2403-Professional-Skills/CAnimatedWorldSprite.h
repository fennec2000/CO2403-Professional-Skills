// CAnimatedWorldSprite.h 01-03-2018
// William John Atkin WJAtkin@UCLan.ac.uk

#pragma once
#include "BUILD_ORDER.h"

class CAnimatedWorldSprite : protected CWorldSprite
{
public:
	CAnimatedWorldSprite(vector<const char*> spriteList, SVector3D<float> position);
	~CAnimatedWorldSprite();

	// Animation functions
	void StartAnimation();
	void StopAnimation();
	void RestartAnimation();

private:
	vector<const char*> mSpriteList;

	// Animation variables
	int mAnimationSpeed = 2;
	int mSpriteAnimationPosition = 0;
};

