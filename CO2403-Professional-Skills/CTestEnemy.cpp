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
	pC->AddEnemy(*this);
}

CTestEnemy::~CTestEnemy()
{
	pC->RemoveEnemy(*this);
}

void CTestEnemy::Update()
{
	float playerX = pC->GetPlayer(PlayerTeam)->GetX();
	float playerY = pC->GetPlayer(PlayerTeam)->GetY();
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
	newBullet.bulletTimeMax = 3.0f;
	newBullet.Speed = 1.5f;
	CPlayer* target = pC->GetPlayer(PlayerTeam);
	SVector2D<float> vec = target->GetPos2D() - pCharSprite->GetPosition2D();
	newBullet.travelVector = vec.Normalised();

	// create bullet
	new CBullet(newBullet);
}

void CTestEnemy::Death()
{

}