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
	pCharSprite->SetSpriteSkin("Player.png");
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
		SVector2D<float> currentMove = mRollVector;
		currentMove.x *= *pFrameTimer * mROLL_SPEED;
		currentMove.y *= *pFrameTimer * mROLL_SPEED;
		Move(currentMove);
		mRollCurrent -= *pFrameTimer * mROLL_SPEED;
	}
	else 
	{
		if (mMovement.x != 0.0f || mMovement.y != 0.0f)
			Move(mMovement);

		// rotate
		pCharSprite->LookAt(pCursor);
	}

	// cooldowns
	if (mFireTimeCurrent > 0.0f)
		mFireTimeCurrent -= *pFrameTimer;

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
		if (pTLEngine->KeyHeld(mPlayerFire) && mFireTimeCurrent <= 0.0f)
		{
			Shoot();
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

void CPlayer::Death()
{

}

void CPlayer::ChangeHealth(int change)
{
	if (!mCheatGod || mRollCurrent <= 0.0f)
		CCharacter::ChangeHealth(change);
}

void CPlayer::Move(SVector2D<float> movement)
{
	SVector2D<float> moveCursor = CCharacter::Move(movement);
	pCursor->MoveX(moveCursor.x);
	pCursor->MoveY(moveCursor.y);
}

void CPlayer::Shoot()
{
	// Setup bullet
	bulletSetup newBullet;
	newBullet.spawnPos = GetPos3D();
	newBullet.bulletTimeMax = 3.0f;
	newBullet.Speed = 1.5f;
	SVector2D<float> vec = pCursor->GetPosition2D() - pCharSprite->GetPosition2D();
	newBullet.travelVector = vec.Normalised();

	// create bullet
	new CBullet(newBullet);

	// fire timer
	mFireTimeCurrent = mFireTimeMax;
}