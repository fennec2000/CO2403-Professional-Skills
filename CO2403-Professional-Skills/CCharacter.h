#pragma once
#include "BUILD_ORDER.h"
// This class has the base functions that both the player and enemies have

class CCharacter
{
private:

protected:
	CCore* mpC;
	CWorldSprite* mpCharSprite;
	tle::I3DEngine* mpTLEngine;
	float* mpFrameTimer;
	unsigned int mHealthMax;
	unsigned int mHealthCurrent;

public:
	CCharacter();
	~CCharacter();

	virtual void Update() = 0;
	virtual void Death() = 0;

	void ChangeHealth(int change); // Changes the characters health, use -ve to damage, use +ve to heal
	void SetPosition(float x, float y, float z) { mpCharSprite->SetPosition({x, y, z}); };
};