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
	float playerX = mpC->GetPlayer(Player1)->GetX();
	float playerY = mpC->GetPlayer(Player1)->GetY();
	float enemyX = mpCharSprite->GetX();
	float enemyY = mpCharSprite->GetY();
	
	if(isActive)
	{
		if (enemyX > playerX)
		{
			mpCharSprite->MoveX(-mMoveSpeed * *mpFrameTimer);
		}
		if (enemyX < playerX)
		{
			mpCharSprite->MoveX(mMoveSpeed * *mpFrameTimer);
		}
		if (enemyY > playerY)
		{
			mpCharSprite->MoveY(-mMoveSpeed * *mpFrameTimer);
		}
		if (enemyY < playerY)
		{
			mpCharSprite->MoveY(mMoveSpeed * *mpFrameTimer);
		}
	}
	if (shot == false)
	{
		mpC->AddBullet(enemyX, enemyY, 0);	

	}
	else if (shot == true)
	{

	}
	
	

}