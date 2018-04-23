#include "BUILD_ORDER.h"



CPowerUp::CPowerUp()
{
	c = CCore::GetInstance();
}


CPowerUp::~CPowerUp()
{
	delete pWorldSprite;
}