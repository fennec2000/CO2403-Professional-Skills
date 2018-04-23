#include "BUILD_ORDER.h"


CEnemyChaingun::CEnemyChaingun()
{
	toggleActive();
}

CEnemyChaingun::CEnemyChaingun(float x, float y, float z, bool activate)
{
	SetPosition(x, y, z);
	isActive = activate;
	pCharSprite->SetSpriteSkin("derp.png");
	pLevel = pC->GetLevel();
}

CEnemyChaingun::~CEnemyChaingun()
{
	
}

void CEnemyChaingun::Update()
{

}

bool CEnemyChaingun::EUpdate()
{
	if (currentHealth <= 0)
	{
		Death();
		return true;
	}

	if (isActive && !isShooting && *pFrameTimer < 1.0f)
	{
		SVector2D<float> eMovement;
		SVector2D<float> testPos;
		SVector2D<float> playerPos = { pC->GetPlayer(PlayerTeam)->GetX(), pC->GetPlayer(PlayerTeam)->GetY() };
		SVector2D<float> vec = pC->GetPlayer(PlayerTeam)->GetPos2D() - pCharSprite->GetPosition2D();
		SVector2D<float> ePos = pCharSprite->GetPosition2D();

		eMovement.x = (vec.x * *pFrameTimer * mMoveSpeed);
		eMovement.y = (vec.y * *pFrameTimer * mMoveSpeed);
		testPos = { ePos.x + eMovement.x, ePos.y + eMovement.y };
		if (!CollisionCheck(testPos))
		{
			pCharSprite->MoveX(eMovement.x);
			pCharSprite->MoveY(eMovement.y);
		}
	}

	if (bulletTimer < MAX_BULLET_TIMER && !isShooting)
	{
		bulletTimer = bulletTimer + *pFrameTimer;
	}
	else
	{
		isShooting = true;
	}

	if (isShooting)
	{
		if (chaingunFireTime < MAX_CHAINGUN_FIRE_TIME)
		{
			chaingunFireTime = chaingunFireTime + *pFrameTimer;

			if (currentRevTime < chaingunMaxRevTime)
			{
				currentRevTime = currentRevTime + *pFrameTimer;
			}
			else
			{
				Shoot();
				currentRevTime = 0.0f;
				if (chaingunMaxRevTime - CHAINGUN_REV_DECREMENT > MIN_CHAINGUN_BULLET_TIME) chaingunMaxRevTime = chaingunMaxRevTime - CHAINGUN_REV_DECREMENT;
			}
		}
		else
		{
			chaingunFireTime = 0.0f;
			currentRevTime = 0.0f;
			chaingunMaxRevTime = 1.5f;
			bulletTimer = 0.0f;
			isShooting = false;
		}

	}

	return false;
}

void CEnemyChaingun::Shoot()
{
	// Setup bullet
	SVector2D<float> adjustedBullet;
	float bulletSpreadAngle = rand() % 90;
	bulletSpreadAngle = bulletSpreadAngle - 45;
	float firingAngle = bulletSpreadAngle * 3.14 / 180;
	bulletSetup newBullet;
	newBullet.spawnPos = GetPos3D();
	newBullet.BulletTimeMax = 3.0f;
	newBullet.Speed = 1.5f;
	CPlayer* target = pC->GetPlayer(PlayerTeam);
	SVector2D<float> vec = target->GetPos2D() - pCharSprite->GetPosition2D();
	newBullet.travelVector = vec.Normalised();
	adjustedBullet.x = newBullet.travelVector.x * cos(firingAngle) - newBullet.travelVector.y * sin(firingAngle);
	adjustedBullet.y = newBullet.travelVector.x * sin(firingAngle) + newBullet.travelVector.y * cos(firingAngle);
	newBullet.travelVector = adjustedBullet;
	// create bullet
	new CBullet(newBullet);
}

void CEnemyChaingun::Hit()
{
	currentHealth = currentHealth - 1;
}

void CEnemyChaingun::Death()
{
	cout << "death" << endl;
	if (rand() % 100 < DROP_SHOTGUN_CHANCE)
		pC->pPowerUps.push_back(new CPowerShotgun(pCharSprite->GetPosition2D()));
	CEnemyChaingun::~CEnemyChaingun();
}