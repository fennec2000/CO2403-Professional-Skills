#include "BUILD_ORDER.h"

CEProjectile::CEProjectile()
{
	
}

CEProjectile::CEProjectile(float x, float y, float z)
{
	SetPosition(x, y, z);
	mpCharSprite->SetSpriteSkin("Cacodemon_tlxcutout.png");
}

CEProjectile::~CEProjectile()
{
	mpCharSprite->~CWorldSprite();
}

void CEProjectile::Update()
{
	if (lifetime < maxLifetime)
	{
		mpCharSprite->MoveX(-eMoveSpeed * *mpFrameTimer);
		lifetime = lifetime + *mpFrameTimer;
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

