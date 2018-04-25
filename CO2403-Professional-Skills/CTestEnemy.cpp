#include "BUILD_ORDER.h"
#include "math.h"

CTestEnemy::CTestEnemy(float x, float y, float z, bool activate)
{
	SetPosition(x, y, z);
	isActive = activate;
	pCharSprite->SetSpriteSkin("hitman1_gun.png");
	pLevel = pC->GetLevel();
	gunSound = new CAudio("Media\\Sound\\ShotgunSound.wav", false);
}

CTestEnemy::~CTestEnemy()
{	//delete pCharSprite;
	delete gunSound;
}

void CTestEnemy::Update()
{
}

bool CTestEnemy::EUpdate()
{
	if (currentHealth <= 0)
	{
		Death();
		return true;
	}

	if (*pFrameTimer < 1.0f)
	{
		SVector2D<float> testPos;
		SVector2D<float> playerPos = { pC->GetPlayer(PlayerTeam)->GetX(), pC->GetPlayer(PlayerTeam)->GetY() };
		SVector2D<float> vec = pC->GetPlayer(PlayerTeam)->GetPos2D() - pCharSprite->GetPosition2D();
		SVector2D<float> ePos = pCharSprite->GetPosition2D();
		pCharSprite->LookAt(playerPos.x, playerPos.y, pC->GetPlayer(PlayerTeam)->GetZ());
		float frameSpeed = mMoveSpeed * *pFrameTimer;
		vec = vec.Normalised();

		testPos = { ePos.x + spriteSizeX + vec.x * frameSpeed, ePos.y + spriteSizeY + vec.y * frameSpeed };
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

void CTestEnemy::Shoot()
{
	// Setup bullet
	SVector2D<float> vec2;
	SVector2D<float> vec3;
	bulletSetup newBullet;
	newBullet.spawnPos = GetPos3D();
	newBullet.BulletTimeMax = 3.0f;
	newBullet.Speed = 1.5f;
	CPlayer* target = pC->GetPlayer(PlayerTeam);
	SVector2D<float> vec = target->GetPos2D() - pCharSprite->GetPosition2D();
	newBullet.travelVector = vec.Normalised();
	// create bullet
	new CBullet(newBullet);
	// fire sound
	gunSound->Play();
}

void CTestEnemy::Hit()
{
	currentHealth = currentHealth - 1;
}

void CTestEnemy::Death()
{
	pC->AddScore(POINTS);
	delete this;
}