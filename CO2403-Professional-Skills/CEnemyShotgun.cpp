#include "BUILD_ORDER.h"
#include "math.h"

CEnemyShotgun::CEnemyShotgun(float x, float y, float z, bool activate)
{
	SetPosition(x, y, z);
	isActive = activate;
	pCharSprite->SetSpriteSkin("zoimbie1_gun.png");
	pLevel = pC->GetLevel();
	gunSound = new CAudio("Media\\Sound\\ShotgunSound.wav", false);
}

CEnemyShotgun::~CEnemyShotgun()
{	//delete pCharSprite;
	delete gunSound;
}

void CEnemyShotgun::Update()
{
}

bool CEnemyShotgun::EUpdate()
{
	if (currentHealth <= 0)
	{
		Death();
		return true;
	}

	
	if (*pFrameTimer < 1.0f)
	{
		SVector2D<float> eMovement;
		SVector2D<float> testPos;
		SVector2D<float> playerPos = { pC->GetPlayer(PlayerTeam)->GetX(), pC->GetPlayer(PlayerTeam)->GetY() };
		SVector2D<float> vec = pC->GetPlayer(PlayerTeam)->GetPos2D() - pCharSprite->GetPosition2D();
		SVector2D<float> ePos = pCharSprite->GetPosition2D();
		pCharSprite->LookAt(playerPos.x, playerPos.y, pC->GetPlayer(PlayerTeam)->GetZ());
		float frameSpeed = mMoveSpeed * *pFrameTimer;
		vec = vec.Normalised();






			testPos = { ePos.x + spriteSizeX + vec.x * frameSpeed, ePos.y + spriteSizeY + vec.y * frameSpeed};
			if (!CollisionCheck(testPos))
			{
				pCharSprite->MoveX(vec.x * frameSpeed);
				pCharSprite->MoveY(vec.y * frameSpeed);
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
	return false;
}

void CEnemyShotgun::Shoot()
{
	// Setup bullet
	float firingAngle = bulletSpreadAngle * PI / 180.0f;
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

	// fire sound
	gunSound->Play();
}

void CEnemyShotgun::Hit()
{
	currentHealth = currentHealth - 1;
}

void CEnemyShotgun::Death()
{
	pC->AddScore(POINTS);
	if (rand() % 100 < DROP_SHOTGUN_CHANCE)
		pC->pPowerUps.push_back(new CPowerShotgun(pCharSprite->GetPosition2D()));
	delete this;
}