#include "BUILD_ORDER.h"

CPlayer::CPlayer(EPlayers player)
{
	pC->AddPlayer(player, *this);
}

CPlayer::CPlayer(EPlayers player, float x, float y, float z)
{
	// varable setup
	mRollCurrent = 0.0f;

	// setup
	pCamera = pC->GetCamera();
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
	InputCheck();
	if (mRollCurrent > 0.0f)
	{
		pCharSprite->MoveX(mRollVector.x * *pFrameTimer * mROLL_SPEED);
		pCursor->MoveX(mRollVector.x * *pFrameTimer * mROLL_SPEED);
		pCharSprite->MoveY(mRollVector.y * *pFrameTimer * mROLL_SPEED);
		pCursor->MoveY(mRollVector.y * *pFrameTimer * mROLL_SPEED);
		mRollCurrent -= *pFrameTimer * mROLL_SPEED;
	}

	// update camera
	SVector2D<float> playerPos = pCharSprite->GetPosition2D();
	pCamera->SetPosition(playerPos.x + mCAMERA_OFFSET.x, playerPos.y + mCAMERA_OFFSET.y, mCAMERA_OFFSET.z);
}

void CPlayer::InputCheck()
{
	pCursor->MoveX(pTLEngine->GetMouseMovementX() * *pFrameTimer);
	pCursor->MoveY(-pTLEngine->GetMouseMovementY() * *pFrameTimer);
	
	// keybindings
	if (pTLEngine->KeyHeld(mPlayerFire))
	{
		
	}
	if (mRollCurrent <= 0.0f)
	{
		if (pTLEngine->KeyHeld(mPlayerRoll))
		{
			// roll
			SVector2D<float> charPos = pCharSprite->GetPosition2D();
			SVector2D<float> cursorPos = pCursor->GetPosition2D();
			mRollVector.x = cursorPos.x - charPos.x;
			mRollVector.y = cursorPos.y - charPos.y;
			float lenght = sqrt(mRollVector.x * mRollVector.x + mRollVector.y * mRollVector.y);
			mRollVector.x /= lenght;
			mRollVector.y /= lenght;

			mRollCurrent = mROLL_DISTANCE_MAX;
		}
		if (pTLEngine->KeyHeld(mPlayerMoveUp))
		{
			pCharSprite->MoveY(mMoveSpeed * *pFrameTimer);
			pCursor->MoveY(mMoveSpeed * *pFrameTimer);
		}
		if (pTLEngine->KeyHeld(mPlayerMoveLeft))
		{
			pCharSprite->MoveX(-mMoveSpeed * *pFrameTimer);
			pCursor->MoveX(-mMoveSpeed * *pFrameTimer);
		}
		if (pTLEngine->KeyHeld(mPlayerMoveDown))
		{
			pCharSprite->MoveY(-mMoveSpeed * *pFrameTimer);
			pCursor->MoveY(-mMoveSpeed * *pFrameTimer);
		}
		if (pTLEngine->KeyHeld(mPlayerMoveRight))
		{
			pCharSprite->MoveX(mMoveSpeed * *pFrameTimer);
			pCursor->MoveX(mMoveSpeed * *pFrameTimer);
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