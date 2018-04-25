#include "BUILD_ORDER.h"
#include "math.h"

CEnemyShotgun::CEnemyShotgun(float x, float y, float z, bool activate)
{
	SetPosition(x, y, z);
	isActive = activate;
	pCharSprite->SetSpriteSkin("derp.png");
	pLevel = pC->GetLevel();
}

CEnemyShotgun::~CEnemyShotgun()
{
	//cout << "Hep, am ded";
	//delete pCharSprite;
}
void CEnemyShotgun::Update()
{
	//cout << "meggle";
}

bool CEnemyShotgun::EUpdate()
{
	if (currentHealth <= 0)
	{
		Death();
		return true;
	}

	SVector2D<float> eMovement;
	SVector2D<float> testPos;
	SVector2D<float> playerPos = { pC->GetPlayer(PlayerTeam)->GetX(), pC->GetPlayer(PlayerTeam)->GetY() };
	SVector2D<float> vec = pC->GetPlayer(PlayerTeam)->GetPos2D() - pCharSprite->GetPosition2D();
	SVector2D<float> ePos = pCharSprite->GetPosition2D();
	float distance = sqrt(((playerPos.x - ePos.x) * (playerPos.x - ePos.x)) + ((playerPos.y - ePos.y) * (playerPos.y - ePos.y)));
	if (distance < DISTANCE_TO_KEEP)
	{
		eMovement.x = (-vec.x * *pFrameTimer * mMoveSpeed);
		eMovement.y = (-vec.y * *pFrameTimer * mMoveSpeed);
		testPos = { ePos.x + eMovement.x, ePos.y + eMovement.y };
		if (!CollisionCheck(testPos))
		{
			pCharSprite->MoveX(eMovement.x);
			pCharSprite->MoveY(eMovement.y);
		}
	}
	else
	{
		eMovement.x = (vec.x * *pFrameTimer * mMoveSpeed);
		eMovement.y = (vec.y * *pFrameTimer * mMoveSpeed);
		testPos = { ePos.x + eMovement.x, ePos.y + eMovement.y };
		if (!CollisionCheck(testPos))
		{
			pCharSprite->MoveX(eMovement.x);
			pCharSprite->MoveY(eMovement.y);
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
	return false;
}

void CEnemyShotgun::Shoot()
{
	// Setup bullet
	float firingAngle = bulletSpreadAngle * 3.14 / 180;
	SVector2D<float> vec2;
	SVector2D<float> vec3;
	bulletSetup newBullet;
	newBullet.spawnPos = GetPos3D();
	newBullet.BulletTimeMax = 3.0f;
	newBullet.Speed = 1.5f;
	CPlayer* target = pC->GetPlayer(PlayerTeam);
	SVector2D<float> vec = target->GetPos2D() - pCharSprite->GetPosition2D();
	newBullet.travelVector = vec.Normalised();
	vec2.x = newBullet.travelVector.x * cos(firingAngle) - newBullet.travelVector.y * sin(firingAngle);
	vec2.y = newBullet.travelVector.x * sin(firingAngle) + newBullet.travelVector.y * cos(firingAngle);
	vec3.x = newBullet.travelVector.x * cos(-firingAngle) - newBullet.travelVector.y * sin(-firingAngle);
	vec3.y = newBullet.travelVector.x * sin(-firingAngle) + newBullet.travelVector.y * cos(-firingAngle);
	// create bullet
	new CBullet(newBullet);
	newBullet.travelVector = vec2;
	new CBullet(newBullet);
	newBullet.travelVector = vec3;
	new CBullet(newBullet);
}

void CEnemyShotgun::Hit()
{
	currentHealth = currentHealth - 1;
}

void CEnemyShotgun::Death()
{
	//cout << "death" << endl;
	if (rand() % 100 < DROP_SHOTGUN_CHANCE)
		pC->pPowerUps.push_back(new CPowerShotgun(pCharSprite->GetPosition2D()));
	delete this;
}