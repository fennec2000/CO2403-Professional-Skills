#include "BUILD_ORDER.h"
#include "math.h"

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
	// Setup bullet
	float firingAngle = bulletSpreadAngle * 3.14 / 180;
	SVector2D<float> vec2;
	SVector2D<float> vec3;
	bulletSetup newBullet;
	newBullet.spawnPos = GetPos3D();
	newBullet.BulletTimeMax = 3.0f;
	newBullet.Speed = 1.5f;
	CPlayer* target = pC->GetPlayer(Player1);
	SVector2D<float> vec = target->GetPos2D() - pCharSprite->GetPosition2D();
	newBullet.travelVector = vec.Normalised();
	vec2.x = newBullet.travelVector.x * cos(firingAngle) - newBullet.travelVector.y * sin(firingAngle);
	vec2.y = newBullet.travelVector.x * sin(firingAngle) + newBullet.travelVector.y * cos(firingAngle);
	vec3.x = newBullet.travelVector.x * cos(-firingAngle) - newBullet.travelVector.y * sin(-firingAngle);
	vec3.y = newBullet.travelVector.x * sin(-firingAngle) + newBullet.travelVector.y * cos(-firingAngle);
	// create bullet
	new CBullet(newBullet);
	newBullet.travelVector = vec2;
	new CBullet(newBullet);
	newBullet.travelVector = vec3;
	new CBullet(newBullet);
}

void CEnemyShotgun::Death()
{

}