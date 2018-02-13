#pragma once
#include <TL-Engine.h>
#include "CCore.h"
#include "BUILD_ORDER.h"
// This class has the base functions that both the player and enemies have

class CCharacter
{
private:
	CCore* mC;
	tle::I3DEngine* mpTLEngine;
	CWorldSprite* mpCharSprite;
public:
	CCharacter();
	~CCharacter();

	void SetPosition(float x, float y, float z) { mpCharSprite->SetPosition({x, y, z}); };
};