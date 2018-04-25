#pragma once
#include "BUILD_ORDER.h"

enum EPowerUps { GiveShotgun, MoveSpeedUp };

struct SPowerUpInfo
{
	EPowerUps power;
	int strenght;
};

class CPowerUp
{
protected:
	CCore* c;
public:
	CWorldSprite * pWorldSprite;
	CPowerUp();
	virtual SPowerUpInfo GetEffect() = 0;
	virtual ~CPowerUp();
};

