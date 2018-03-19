#include "CBullet.h"


CBullet::CBullet(bulletSetup &givenSetup)
{
	pC = CCore::GetInstance();
	pCharSprite = new CWorldSprite(givenSetup.spriteFileName.c_str(), givenSetup.spawnPos);
	pFrameTimer = pC->GetFrameTimer();
	mVector = givenSetup.travelVector;
	mBulletTimerMax = givenSetup.BulletTimeMax;
	mMoveSpeed = givenSetup.Speed;
	mTeam = givenSetup.team;
	pC->AddBullet(*this);
}


CBullet::~CBullet()
{
	pCharSprite->~CWorldSprite();
}

void CBullet::Update()
{
	pCharSprite->MoveX(mVector.x * *pFrameTimer * mMoveSpeed);
	pCharSprite->MoveY(mVector.y * *pFrameTimer * mMoveSpeed);
	mBulletTimerCurrent += *pFrameTimer;
	if (mBulletTimerCurrent >= mBulletTimerMax)
	{
		pC->RemoveBullet(*this);
		CBullet::~CBullet();
	}

	// collisions

}