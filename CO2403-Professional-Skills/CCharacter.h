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

public:
	CCharacter();
	~CCharacter();

	virtual void Update() = 0;

	void SetPosition(float x, float y, float z) { mpCharSprite->SetPosition({x, y, z}); };
};