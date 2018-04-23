#pragma once
#include "BUILD_ORDER.h"

enum EPowerUps { GiveShotgun, MoveSpeedUp };

class CPowerUp
{
protected:
	CCore* c;
public:
	CWorldSprite * pWorldSprite;
	CPowerUp();
	virtual ~CPowerUp();
};

