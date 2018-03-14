#include "BUILD_ORDER.h"

CTestEnemy::CTestEnemy()
{
	toggleActive();
}

CTestEnemy::CTestEnemy(float x, float y, float z, bool activate)
{
	SetPosition(x, y, z);
	isActive = activate;
	pCharSprite->SetSpriteSkin("derp.png");
}

CTestEnemy::~CTestEnemy()
{

}

void CTestEnemy::Update()
{
	float playerX = pC->GetPlayer(Player1)->GetX();
	float playerY = pC->GetPlayer(Player1)->GetY();
	float enemyX = pCharSprite->GetX();
	float enemyY = pCharSprite->GetY();

	if (isActive)
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

	// shooting
	mShootTimerCurrent += *pFrameTimer;
	if (mShootTimerCurrent >= mShootTimerMax)
	{
		Shoot();
		mShootTimerCurrent = 0.0f;
	}
}

void CTestEnemy::Shoot()
{
	// Setup bullet
	bulletSetup newBullet;
	newBullet.spawnPos = GetPos3D();
	newBullet.BulletTimeMax = 3.0f;
	newBullet.Speed = 1.5f;
	CPlayer* target = pC->GetPlayer(Player1);
	SVector2D<float> vec = target->GetPos2D() - pCharSprite->GetPosition2D();
	newBullet.travelVector = vec.Normalised();

	// create bullet
	new CBullet(newBullet);
}

void CTestEnemy::Death()
{

}