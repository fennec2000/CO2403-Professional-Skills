#include "BUILD_ORDER.h"


CEnemyChaingun::CEnemyChaingun()
{
	toggleActive();
}

CEnemyChaingun::CEnemyChaingun(float x, float y, float z, bool activate)
{
	SetPosition(x, y, z);
	isActive = activate;
	pCharSprite->SetSpriteSkin("derp.png");
}

CEnemyChaingun::~CEnemyChaingun()
{

}

void CEnemyChaingun::Update()
{
	float playerX = pC->GetPlayer(PlayerTeam)->GetX();
	float playerY = pC->GetPlayer(PlayerTeam)->GetY();
	float enemyX = pCharSprite->GetX();
	float enemyY = pCharSprite->GetY();

	if (isActive && !isShooting)
	{
		if (enemyX > playerX)
		{
			pCharSprite->MoveX(-mMoveSpeed * *pFrameTimer);
		}
		if (enemyX < playerX)
		{
			pCharSprite->MoveX(mMoveSpeed * *pFrameTimer);
		}
		if (enemyY > playerY)
		{
			pCharSprite->MoveY(-mMoveSpeed * *pFrameTimer);
		}
		if (enemyY < playerY)
		{
			pCharSprite->MoveY(mMoveSpeed * *pFrameTimer);
		}
	}

	if (bulletTimer < MAX_BULLET_TIMER && !isShooting)
	{
		bulletTimer = bulletTimer + *pFrameTimer;
	}
	else
	{
		isShooting = true;
	}

	if (isShooting)
	{
		if (chaingunFireTime < MAX_CHAINGUN_FIRE_TIME)
		{
			chaingunFireTime = chaingunFireTime + *pFrameTimer;

			if (currentRevTime < chaingunMaxRevTime)
			{
				currentRevTime = currentRevTime + *pFrameTimer;
			}
			else
			{
				Shoot();
				currentRevTime = 0.0f;
				if (chaingunMaxRevTime - CHAINGUN_REV_DECREMENT > MIN_CHAINGUN_BULLET_TIME) chaingunMaxRevTime = chaingunMaxRevTime - CHAINGUN_REV_DECREMENT;
			}
		}
		else
		{
			chaingunFireTime = 0.0f;
			currentRevTime = 0.0f;
			chaingunMaxRevTime = 1.5f;
		}

	}



}

void CEnemyChaingun::Shoot()
{
	// Setup bullet
	SVector2D<float> adjustedBullet;
	float bulletSpreadAngle = rand() % 90;
	bulletSpreadAngle = bulletSpreadAngle - 45;
	float firingAngle = bulletSpreadAngle * 3.14 / 180;
	bulletSetup newBullet;
	newBullet.spawnPos = GetPos3D();
	newBullet.BulletTimeMax = 3.0f;
	newBullet.Speed = 1.5f;
	CPlayer* target = pC->GetPlayer(PlayerTeam);
	SVector2D<float> vec = target->GetPos2D() - pCharSprite->GetPosition2D();
	newBullet.travelVector = vec.Normalised();
	adjustedBullet.x = newBullet.travelVector.x * cos(firingAngle) - newBullet.travelVector.y * sin(firingAngle);
	adjustedBullet.y = newBullet.travelVector.x * sin(firingAngle) + newBullet.travelVector.y * cos(firingAngle);
	newBullet.travelVector = adjustedBullet;
	// create bullet
	new CBullet(newBullet);
}

void CEnemyChaingun::Death()
{
	
}