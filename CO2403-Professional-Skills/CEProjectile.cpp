#include "BUILD_ORDER.h"

CEProjectile::CEProjectile()
{
	
}

CEProjectile::CEProjectile(float x, float y, float z, SVector2D<float> bulletVector)
{
	SetPosition(x, y, z);
	pCharSprite->SetSpriteSkin("Cacodemon_tlxcutout.png");
	mVector = bulletVector;
}

CEProjectile::~CEProjectile()
{
	pCharSprite->~CWorldSprite();
}

void CEProjectile::Update()
{
	if (lifetime < maxLifetime)
	{
		lifetime = lifetime + *pFrameTimer;
		pCharSprite->MoveX(mVector.x * *pFrameTimer * eMoveSpeed);
		pCharSprite->MoveY(mVector.y * *pFrameTimer * eMoveSpeed);
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

