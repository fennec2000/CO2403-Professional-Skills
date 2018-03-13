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
	pC->enemies.push_back(this);
}

CEnemyChaingun::~CEnemyChaingun()
{

}

void CEnemyChaingun::Update()
{
	float playerX = pC->GetPlayer(Player1)->GetX();
	float playerY = pC->GetPlayer(Player1)->GetY();
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
	float bulletSpreadAngle = rand() % 90;
	bulletSpreadAngle = bulletSpreadAngle - 45;
	float firingAngle = bulletSpreadAngle * 3.14 / 180;


	float enemyX = pCharSprite->GetX();
	float enemyY = pCharSprite->GetY();
	SVector2D<float> enemyPos = pCharSprite->GetPosition2D();
	SVector2D<float> playerPos;
	SVector2D<float> adjustedBullet;
	playerPos.x = pC->GetPlayer(Player1)->GetX();
	playerPos.y = pC->GetPlayer(Player1)->GetY();
	mFireVector.x = playerPos.x - enemyPos.x;
	mFireVector.y = playerPos.y - enemyPos.y;
	float lenght = sqrt(mFireVector.x * mFireVector.x + mFireVector.y * mFireVector.y);
	mFireVector.x /= lenght;
	mFireVector.y /= lenght;
	adjustedBullet.x = mFireVector.x * cos(firingAngle) - mFireVector.y * sin(firingAngle);
	adjustedBullet.y = mFireVector.x * sin(firingAngle) + mFireVector.y * cos(firingAngle);
	pC->AddBullet(enemyX, enemyY, adjustedBullet);
}

void CEnemyChaingun::Death()
{

}