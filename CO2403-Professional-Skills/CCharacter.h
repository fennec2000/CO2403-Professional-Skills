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
	float* pFrameTimer;
	unsigned int mHealthMax;
	unsigned int mHealthCurrent;

public:
	CCharacter();
	~CCharacter();

	virtual void Update() = 0;
	virtual void Death() = 0;

	void ChangeHealth(int change); // Changes the characters health, use -ve to damage, use +ve to heal
	void SetPosition(float x, float y, float z) { pCharSprite->SetPosition({x, y, z}); };
};