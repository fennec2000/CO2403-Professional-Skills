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
	pLevel = pC->GetLevel();
}


CBullet::~CBullet()
{
	if (pCharSprite != NULL)
		delete pCharSprite;
}

void CBullet::Update()
{
	SVector2D<float> myPos = pCharSprite->GetPosition2D();
	myPos.x = myPos.x + 0.5f;
	myPos.y = myPos.y + 0.5f;

	if (!CollisionCheck(myPos))
	{
		pCharSprite->MoveX(mVector.x * *pFrameTimer * mMoveSpeed);
		pCharSprite->MoveY(mVector.y * *pFrameTimer * mMoveSpeed);
	}
	else
	{
		Remove();
		return;
	}
	mBulletTimerCurrent += *pFrameTimer;
	if (mBulletTimerCurrent >= mBulletTimerMax)
	{
		Remove();
		return;
	}
}

void CBullet::Remove()
{
	pC->RemoveBullet(*this);
	delete this;
}

bool CBullet::CollisionCheck(SVector2D<float> pos)
{
	// get center
	// sphere collision

	ETileType test = pLevel->GetTile(pos);
	if (test == ETileType::WALL || test == ETileType::WALL_WITH_SIDE || test == ETileType::WALL_WITH_SIDE_FLIPPED_Y || test == ETileType::DOOR || test == ETileType::DOOR_ROT || test == ETileType::DOOR_OPEN || test == ETileType::DOOR_ROT_OPEN)
		return true;
	return false;
}