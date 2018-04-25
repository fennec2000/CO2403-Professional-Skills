#pragma once
#include "BUILD_ORDER.h"
// This class has the base functions that both the player and enemies have

class CCharacter
{
private:

protected:
	CCore* pC;
	CWorldSprite* pCharSprite;
	tle::I3DEngine* pTLEngine;
	CLevel* pLevel;
	float* pFrameTimer;

	const SVector2D<float> mCharSize = { 1.0f, 1.0f }; // x, y
	const float mCharLeway = 0.1f;
	unsigned int mHealthMax = 3;
	unsigned int mHealthCurrent;
	float mMoveSpeed = 2.0f;
	SVector2D<float> mOldPos;

	SVector2D<float> Move(SVector2D<float> movement);
	bool CollisionCheck(SVector2D<float> pos);

public:
	CCharacter();
	virtual ~CCharacter();

	virtual void Update() = 0;
	virtual void Death() = 0;

	void ChangeHealth(int change); // Changes the characters health, use -ve to damage, use +ve to heal
	void SetPosition(float x, float y, float z) { pCharSprite->SetPosition({ x, y, z }); };
	SVector2D<float> GetPos2D() { return pCharSprite->GetPosition2D(); };
	SVector3D<float> GetPos3D() { return pCharSprite->GetPosition3D(); };
};