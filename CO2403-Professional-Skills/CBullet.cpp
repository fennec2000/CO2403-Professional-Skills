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

	// declare varaibles before switch, vs doesnt like it in the statement
	// then populcate in the case that it is needed
	CPlayer* thePlayer;
	vector <CTestEnemy*> enemyList;
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
		enemyList = pC->GetEnemyList();
		for (int i = 0; i < enemyList.size(); ++i)
		{
			if (Distance(&pCharSprite->GetPosition2D(), &enemyList[i]->GetPos2D()) <= mRadius)
			{
				enemyList[i]->ChangeHealth(mBulletDamage);
				CBullet::~CBullet();
			}
		}
		break;
	default:
		break;
	}
}