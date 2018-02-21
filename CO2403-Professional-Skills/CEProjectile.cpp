#include "BUILD_ORDER.h"

CEProjectile::CEProjectile()
{
	
}

CEProjectile::CEProjectile(float x, float y, float z)
{
	SetPosition(x, y, z);
}

CEProjectile::~CEProjectile()
{

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
		
	}


}