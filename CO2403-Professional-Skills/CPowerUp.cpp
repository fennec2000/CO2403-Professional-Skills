#include "BUILD_ORDER.h"



CPowerUp::CPowerUp()
{
	c = CCore::GetInstance();
	c->pPowerUps.push_back(this);
}


CPowerUp::~CPowerUp()
{
	delete pWorldSprite;
}