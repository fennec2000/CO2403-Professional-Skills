#include "BUILD_ORDER.h"
#include "math.h"

CEnemyShotgun::CEnemyShotgun(float x, float y, float z, bool activate)
{
	SetPosition(x, y, z);
	isActive = activate;
	pCharSprite->SetSpriteSkin("derp.png");
	pC->enemies.push_back(this);
}

CEnemyShotgun::~CEnemyShotgun()
{

}

void CEnemyShotgun::Update()
{
	float playerX = pC->GetPlayer(Player1)->GetX();
	float playerY = pC->GetPlayer(Player1)->GetY();
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
	SVector2D<float> playerPos;
	SVector2D<float> bulletOne;
	SVector2D<float> bulletTwo;
	SVector2D<float> bulletThree;
	SVector2D<float> myPos;
	float firingAngle = bulletSpreadAngle * 3.14 / 180;
	myPos.x = pCharSprite->GetX();
	myPos.y = pCharSprite->GetY();
	playerPos.x = pC->GetPlayer(Player1)->GetX();
	playerPos.y = pC->GetPlayer(Player1)->GetY();
	bulletOne.x = playerPos.x - myPos.x;
	bulletOne.y = playerPos.y - myPos.y;
	float length = sqrt(bulletOne.x * bulletOne.x + bulletOne.y * bulletOne.y);
	bulletOne.x = bulletOne.x / length;
	bulletOne.y = bulletOne.y / length;
	bulletTwo.x = bulletOne.x * cos(firingAngle) - bulletOne.y * sin(firingAngle);
	bulletTwo.y = bulletOne.x * sin(firingAngle) + bulletOne.y * cos(firingAngle);
	bulletThree.x = bulletOne.x * cos(-firingAngle) - bulletOne.y * sin(-firingAngle);
	bulletThree.y = bulletOne.x * sin(-firingAngle) + bulletOne.y * cos(-firingAngle);
	pC->AddBullet(myPos.x, myPos.y, bulletOne);
	pC->AddBullet(myPos.x, myPos.y, bulletTwo);
	pC->AddBullet(myPos.x, myPos.y, bulletThree);
}

void CEnemyShotgun::Death()
{

}