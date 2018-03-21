#include "BUILD_ORDER.h"

CEnemyShotgun::CEnemyShotgun()
{
	toggleActive();
}

CEnemyShotgun::CEnemyShotgun(float x, float y, float z, bool activate)
{
	SetPosition(x, y, z);
	isActive = activate;
	pCharSprite->SetSpriteSkin("derp.png");
}

CEnemyShotgun::~CEnemyShotgun()
{

}

void CEnemyShotgun::Update()
{
	float playerX = pC->GetPlayer(PlayerTeam)->GetX();
	float playerY = pC->GetPlayer(PlayerTeam)->GetY();
	float enemyX = pCharSprite->GetX();
	float enemyY = pCharSprite->GetY();
	float distance = sqrt(((playerX - enemyX) * (playerX - enemyX)) + ((playerY - enemyY) * (playerY - enemyY)));
	if (isActive)
	{
		if (enemyX > playerX)
		{
			if (distance > DISTANCE_TO_KEEP)
			{
				pCharSprite->MoveX(-mMoveSpeed * *pFrameTimer);
			}
			else
			{
				pCharSprite->MoveX(mMoveSpeed * *pFrameTimer);
			}
			
		}
		if (enemyX < playerX)
		{
			if (distance > DISTANCE_TO_KEEP)
			{
				pCharSprite->MoveX(mMoveSpeed * *pFrameTimer);
			}
			else
			{
				pCharSprite->MoveX(-mMoveSpeed * *pFrameTimer);
			}
			
		}
		if (enemyY > playerY)
		{
			if (distance > DISTANCE_TO_KEEP)
			{
				pCharSprite->MoveY(-mMoveSpeed * *pFrameTimer);
			}
			else
			{
				pCharSprite->MoveY(mMoveSpeed * *pFrameTimer);
			}
			
		}
		if (enemyY < playerY)
		{
			if (distance > DISTANCE_TO_KEEP)
			{
				pCharSprite->MoveY(mMoveSpeed * *pFrameTimer);
			}
			else
			{
				pCharSprite->MoveY(-mMoveSpeed * *pFrameTimer);
			}
			
		}
	}
	if (bulletTimer < MAX_BULLET_TIMER)
	{
		bulletTimer = bulletTimer + *pFrameTimer;
	}
	else
	{
		Shoot();
		bulletTimer = 0;
	}
}

void CEnemyShotgun::Shoot()
{
	float enemyX = pCharSprite->GetX();
	float enemyY = pCharSprite->GetY();
	SVector2D<float> enemyPos = pCharSprite->GetPosition2D();
	SVector2D<float> playerPos;
	SVector2D<float> bulletTwo;
	SVector2D<float> bulletThree;
	playerPos.x = pC->GetPlayer(PlayerTeam)->GetX();
	playerPos.y = pC->GetPlayer(PlayerTeam)->GetY();
	mFireVector.x = playerPos.x - enemyPos.x;
	mFireVector.y = playerPos.y - enemyPos.y;
	bulletTwo.x = playerPos.x - enemyPos.x;
	bulletTwo.y = playerPos.y + 2.0f - enemyPos.y;
	bulletThree.x = playerPos.x - enemyPos.x;
	bulletThree.y = playerPos.y - 2.0 - enemyPos.y;
	float lenght = sqrt(mFireVector.x * mFireVector.x + mFireVector.y * mFireVector.y);
	mFireVector.x /= lenght;
	mFireVector.y /= lenght;
	cout << "x " << mFireVector.x << " y " << mFireVector.y << endl;
	lenght = sqrt(bulletTwo.x * bulletTwo.x + bulletTwo.y * bulletTwo.y);
	bulletTwo.x /= lenght;
	bulletTwo.y /= lenght;
	pC->AddBullet(enemyX, enemyY, bulletTwo);
	lenght = sqrt(bulletThree.x * bulletThree.x + bulletThree.y * bulletThree.y);
	bulletThree.x /= lenght;
	bulletThree.y /= lenght;
	pC->AddBullet(enemyX, enemyY, bulletThree);
	pC->AddBullet(enemyX, enemyY, mFireVector);
}

void CEnemyShotgun::Death()
{

}