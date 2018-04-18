
#include "BUILD_ORDER.h"

CCharacter::CCharacter()
{
	pC = CCore::GetInstance();
	pTLEngine = pC->GetTLEngine();
	pFrameTimer = pC->GetFrameTimer();
	pCharSprite = new CWorldSprite("UglyTile.png", { 5.0f, 0.1f, 5.0f }, BLEND_CUTOUT);
	mHealthCurrent = mHealthMax;
}

CCharacter::~CCharacter()
{
	delete pCharSprite;
}

void CCharacter::ChangeHealth(int change)
{
	if (mHealthCurrent + change <= 0)
	{
		mHealthCurrent = 0;
		Death();
		return;
	}
	else if (mHealthCurrent + change > mHealthMax)
	{
		mHealthMax = mHealthMax;
		return;
	}

	mHealthCurrent += change;
}

SVector2D<float> CCharacter::Move(SVector2D<float> movement)
{
	SVector2D<float> totalMovement = { 0.0f, 0.0f };
	mOldPos = GetPos2D();
	SVector2D<float> testPos[4];
	for (int i = 0; i <= 3; ++i)
	{
		testPos[i] = mOldPos;

		if (i < 2)
			testPos[i].y += mCharLeway;
		else
			testPos[i].y -= mCharLeway;

		if (i % 2 == 0)
			testPos[i].x += mCharLeway;
		else
			testPos[i].x -= mCharLeway;
	}
		

	testPos[1].x += mCharSize.x;
	testPos[2].y += mCharSize.y;
	testPos[3] = testPos[3] + mCharSize;
	SVector2D<float> testMove[2];
	testMove[0] = { movement.x , 0.0f };
	testMove[1] = { 0.0f, movement.y };

	if ((movement.x < 0.0f && !CollisionCheck(testPos[0] + testMove[0]) && !CollisionCheck(testPos[2] + testMove[0])) ||
		(movement.x > 0.0f && !CollisionCheck(testPos[1] + testMove[0]) && !CollisionCheck(testPos[3] + testMove[0])))
	{
		pCharSprite->MoveX(movement.x);
		totalMovement.x += movement.x;
	}

	if ((movement.y < 0.0f && !CollisionCheck(testPos[0] + testMove[1]) && !CollisionCheck(testPos[1] + testMove[1])) ||
		(movement.y > 0.0f && !CollisionCheck(testPos[2] + testMove[1]) && !CollisionCheck(testPos[3] + testMove[1])))
	{
		pCharSprite->MoveY(movement.y);
		totalMovement.y += movement.y;
	}
	return totalMovement;
}

bool CCharacter::CollisionCheck(SVector2D<float> pos)
{
	// get center
	// sphere collision

	ETileType test = pLevel->GetTile(pos);
	if (test == ETileType::WALL || test == ETileType::WALL_WITH_SIDE || test == ETileType::WALL_WITH_SIDE_FLIPPED_Y)
		return true;
	return false;
}