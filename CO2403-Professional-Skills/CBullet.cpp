#include "CBullet.h"


CBullet::CBullet(bulletSetup &givenSetup)
{
	pC = CCore::GetInstance();
	pCharSprite = new CWorldSprite(givenSetup.spriteFileName.c_str(), givenSetup.spawnPos);
	pFrameTimer = pC->GetFrameTimer();
	mVector = givenSetup.travelVector;
	mBulletTimerMax = givenSetup.bulletTimeMax;
	mMoveSpeed = givenSetup.Speed;
	mTeam = givenSetup.team;
	mRadius = givenSetup.spriteRadius;
	mBulletDamage = givenSetup.bulletDamage;
	pC->AddBullet(*this);
}


CBullet::~CBullet()
{
	pC->RemoveBullet(*this);
	pCharSprite->~CWorldSprite();
}

void CBullet::Update()
{
	pCharSprite->MoveX(mVector.x * *pFrameTimer * mMoveSpeed);
	pCharSprite->MoveY(mVector.y * *pFrameTimer * mMoveSpeed);
	mBulletTimerCurrent += *pFrameTimer;
	if (mBulletTimerCurrent >= mBulletTimerMax)
	{
		CBullet::~CBullet();
	}

	CPlayer* thePlayer;
	// collisions
	switch (mTeam)
	{
	case EPlayers::EnemyTeam:
		thePlayer = pC->GetPlayer(EPlayers::PlayerTeam);
		if (Distance(&pCharSprite->GetPosition2D(), &thePlayer->GetPos2D()) <= mRadius)
		{
			thePlayer->ChangeHealth(mBulletDamage);
			CBullet::~CBullet();
		}
		break;
	case EPlayers::PlayerTeam:
		/*for (int i = 0; i < pC->GetEnemyList().size; ++i)
		{

		}*/
		break;
	default:
		break;
	}
}