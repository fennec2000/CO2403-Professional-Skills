#include "BUILD_ORDER.h"

CPlayer::CPlayer(EPlayers player)
{
	pC->AddPlayer(player, *this);
}

CPlayer::CPlayer(EPlayers player, float x, float y, float z)
{
	// varable setup
	mRollCurrent = 0.0f;
	mScreenSize[0] = pTLEngine->GetHeight();
	mScreenSize[1] = pTLEngine->GetWidth();

	// setup
	pCamera = pC->GetCamera();
	pLevel = pC->GetLevel();
	pC->AddPlayer(player, *this);
	SetPosition(x, y, z);
	SVector2D<float> playerPos = pCharSprite->GetPosition2D();
	pCursor = new CWorldSprite("UglyTile.png", { playerPos.x, playerPos.y, G_SPRITE_LAYER_Z_POS[ESpriteLayers::UI] });
	pTLEngine->StartMouseCapture();
}

CPlayer::~CPlayer()
{

}

void CPlayer::Update()
{
	// movement
	mMovement = { 0.0f, 0.0f };
	InputCheck();

	if (mRollCurrent > 0.0f)
	{
		pCharSprite->MoveX(mRollVector.x * *pFrameTimer * mROLL_SPEED);
		pCursor->MoveX(mRollVector.x * *pFrameTimer * mROLL_SPEED);
		pCharSprite->MoveY(mRollVector.y * *pFrameTimer * mROLL_SPEED);
		pCursor->MoveY(mRollVector.y * *pFrameTimer * mROLL_SPEED);
		mRollCurrent -= *pFrameTimer * mROLL_SPEED;
	}
	else if (mMovement.x != 0.0f || mMovement.y != 0.0f)
	{
		Move(mMovement);

		// rotate
		/*SVector2D<float> playerCursorVector = pCursor->GetPosition2D() - pCharSprite->GetPosition2D();
		float rotation = tan(playerCursorVector.y / playerCursorVector.x);
		float newRotation = rotation * 180.0 / PI;
		pCharSprite->RotateZ(newRotation - mRotationCurrent);
		mRotationCurrent = newRotation;*/
	}
		

	// update camera
	SVector2D<float> playerPos = pCharSprite->GetPosition2D();
	pCamera->SetPosition(playerPos.x + mCAMERA_OFFSET.x, playerPos.y + mCAMERA_OFFSET.y, mCAMERA_OFFSET.z);
}

void CPlayer::InputCheck()
{
	pCursor->MoveX(pTLEngine->GetMouseMovementX() * *pFrameTimer);
	pCursor->MoveY(-pTLEngine->GetMouseMovementY() * *pFrameTimer);

	// player rotation


	// keybindings
	if (mRollCurrent <= 0.0f)
	{
		if (pTLEngine->KeyHeld(mPlayerFire))
		{

		}
		if (pTLEngine->KeyHeld(mPlayerRoll))
		{
			// roll
			SVector2D<float> charPos = pCharSprite->GetPosition2D();
			SVector2D<float> cursorPos = pCursor->GetPosition2D();
			mRollVector.x = cursorPos.x - charPos.x;
			mRollVector.y = cursorPos.y - charPos.y;
			float lenght = sqrt(mRollVector.x * mRollVector.x + mRollVector.y * mRollVector.y);
			if (lenght != 0.0f)
			{
				mRollVector.x /= lenght;
				mRollVector.y /= lenght;
				mRollCurrent = mROLL_DISTANCE_MAX;
			}
		}
		if (pTLEngine->KeyHeld(mPlayerMoveUp))
		{
			mMovement.y = mMoveSpeed * *pFrameTimer;
		}
		if (pTLEngine->KeyHeld(mPlayerMoveLeft))
		{
			mMovement.x = -mMoveSpeed * *pFrameTimer;
		}
		if (pTLEngine->KeyHeld(mPlayerMoveDown))
		{
			mMovement.y = -mMoveSpeed * *pFrameTimer;
		}
		if (pTLEngine->KeyHeld(mPlayerMoveRight))
		{
			mMovement.x = mMoveSpeed * *pFrameTimer;
		}
	}
}

void CPlayer::Move(SVector2D<float> movement)
{
	mOldPos = GetPos2D();
	SVector2D<float> testPos[4];
	for (int i = 0; i < 3; ++i)
		testPos[i] = mOldPos;

	testPos[1].x += mCharSize.x;
	testPos[2].y += mCharSize.y;
	testPos[3] = mOldPos + mCharSize;
	SVector2D<float> testMove[2];
	testMove[0] = { movement.x , 0.0f };
	testMove[1] = { 0.0f, movement.y };

	if ((movement.x < 0.0f && !CollisionCheck(testPos[0] + testMove[0]) && !CollisionCheck(testPos[2] + testMove[0])) ||
		(movement.x > 0.0f && !CollisionCheck(testPos[1] + testMove[0]) && !CollisionCheck(testPos[3] + testMove[0])))
	{
		pCharSprite->MoveX(movement.x);
		pCursor->MoveX(movement.x);
	}

	if ((movement.y < 0.0f && !CollisionCheck(testPos[0] + testMove[1]) && !CollisionCheck(testPos[1] + testMove[1])) ||
		(movement.y > 0.0f && !CollisionCheck(testPos[2] + testMove[1]) && !CollisionCheck(testPos[3] + testMove[1])))
	{
		pCharSprite->MoveY(movement.y);
		pCursor->MoveY(movement.y);
	}
}

void CPlayer::Death()
{

}

void CPlayer::ChangeHealth(int change)
{
	if (!mCheatGod || mRollCurrent <= 0.0f)
		CCharacter::ChangeHealth(change);
}

bool CPlayer::CollisionCheck(SVector2D<float> pos)
{
	// get center
	// sphere collision

	ETileType test = pLevel->GetTile(pos);
	if (test == ETileType::WALL || test == ETileType::WALL_WITH_SIDE || test == ETileType::WALL_WITH_SIDE_FLIPPED_Y)
		return true;
	return false;
}