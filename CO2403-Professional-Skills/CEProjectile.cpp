#include "BUILD_ORDER.h"

CEProjectile::CEProjectile()
{
	
}

CEProjectile::CEProjectile(float x, float y, float z)
{
	SetPosition(x, y, z);
	pCharSprite->SetSpriteSkin("Cacodemon_tlxcutout.png");
}

CEProjectile::~CEProjectile()
{
	pCharSprite->~CWorldSprite();
}

void CEProjectile::Update()
{
	if (lifetime < maxLifetime)
	{
		pCharSprite->MoveX(-eMoveSpeed * *pFrameTimer);
		lifetime = lifetime + *pFrameTimer;
	}
	else
	{
		delete(this);
	}


}

float CEProjectile::getLifetime()
{
	return lifetime;
}

