#include "BUILD_ORDER.h"

CTestEnemy::CTestEnemy()
{
	toggleActive();
}

CTestEnemy::CTestEnemy(float x, float y, float z, bool activate)
{
	SetPosition(x, y, z);
	isActive = activate;
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
	
	if(isActive)
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
}

void CTestEnemy::Death()
{

}