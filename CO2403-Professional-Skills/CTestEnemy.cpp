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

void CTestEnemy::Shoot()
 {
	CBullet* 
	SVector2D<float> enemyPos = pCharSprite->GetPosition2D();
	SVector2D<float> playerPos;
	playerPos.x = pC->GetPlayer(Player1)->GetX();
	playerPos.y = pC->GetPlayer(Player1)->GetY();
	mFireVector.x = playerPos.x - enemyPos.x;
	mFireVector.y = playerPos.y - enemyPos.y;
	float lenght = sqrt(mFireVector.x * mFireVector.x + mFireVector.y * mFireVector.y);
	mFireVector.x /= lenght;
	mFireVector.y /= lenght;
	pC->AddBullet(enemyPos.x, enemyPos.y, mFireVector);
	}

void CTestEnemy::Death()
{
	
}