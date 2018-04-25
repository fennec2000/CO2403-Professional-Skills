// CAnimatedWorldSprite.h 01-03-2018
// William John Atkin WJAtkin@UCLan.ac.uk

#pragma once
#include "BUILD_ORDER.h"

class CAnimatedWorldSprite : public CWorldSprite
{
public:
	CAnimatedWorldSprite(vector<const char*> spriteList, SVector3D<float> position);
	~CAnimatedWorldSprite();

	// Animation functions
	void StartAnimation();
	void StopAnimation();
	void RestartAnimation();
	void Update();

private:
	vector<const char*> mSpriteList;

	// Animation variables
	const float DEFAULT_ANIMATION_SPEEED = 0.5f;
	float mAnimationSpeed;
	float mAnimationTimer;
	int mSpriteAnimationPosition;
	bool mAnimationPlaying;
};

