// CAnimatedWorldSprite.cpp 01-03-2018
// William John Atkin WJAtkin@UCLan.ac.uk

#pragma once
#include "BUILD_ORDER.h"

CAnimatedWorldSprite::CAnimatedWorldSprite(vector<const char*> spriteList, SVector3D<float> position)
	: CWorldSprite(spriteList[0], position)
{
	mSpriteList = spriteList;
	mAnimationTimer = 0.0f;
	mAnimationSpeed = DEFAULT_ANIMATION_SPEEED;
	mSpriteAnimationPosition = 0;
	mAnimationPlaying = true;
}

CAnimatedWorldSprite::~CAnimatedWorldSprite() { }

void CAnimatedWorldSprite::StartAnimation()
{
	mAnimationPlaying = true;
}

void CAnimatedWorldSprite::StopAnimation()
{
	mAnimationPlaying = false;
}

void CAnimatedWorldSprite::RestartAnimation()
{
	mSpriteAnimationPosition = 0;
	mAnimationTimer = 0.0f;
	SetSpriteSkin(mSpriteList[0]);
}

// Updates the timer and checks the sprite
void CAnimatedWorldSprite::Update()
{
	if (mAnimationPlaying && mAnimationTimer >= mAnimationSpeed)
	{
		mSpriteAnimationPosition++;
		if (mSpriteAnimationPosition == mSpriteList.size())
		{
			mSpriteAnimationPosition = 0;
		}

		SetSpriteSkin(mSpriteList[mSpriteAnimationPosition]);
		mAnimationTimer = 0.0f;
	}
	else
	{
		mAnimationTimer += (*CCore::GetInstance()->GetFrameTimer());
	}
}