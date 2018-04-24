#include "CBullet.h"

CBullet::CBullet(bulletSetup givenSetup)
{
	pC = CCore::GetInstance();
	pCharSprite = new CWorldSprite(givenSetup.spriteFileName, givenSetup.spawnPos, BLEND_CUTOUT);
	pFrameTimer = pC->GetFrameTimer();
	mVector = givenSetup.travelVector;
	mBulletTimerMax = givenSetup.BulletTimeMax;
	mMoveSpeed = givenSetup.Speed;
	pCharSprite->ResizeSprite(0.25f);
	pC->AddBullet(*this);
	bulletTeam = givenSetup.team;
}


CBullet::~CBullet()
{
	delete pCharSprite;
}

void CBullet::Update()
{
	pCharSprite->MoveX(mVector.x * *pFrameTimer * mMoveSpeed);
	pCharSprite->MoveY(mVector.y * *pFrameTimer * mMoveSpeed);
	mBulletTimerCurrent += *pFrameTimer;
	if (mBulletTimerCurrent >= mBulletTimerMax)
	{
		Remove();
	}
}

void CBullet::Remove()
{
	pC->RemoveBullet(*this);
	CBullet::~CBullet();
}