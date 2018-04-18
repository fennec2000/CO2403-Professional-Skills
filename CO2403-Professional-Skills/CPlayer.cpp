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
	pBullets = pC->GetBullets();
	pGUI = pC->GetGUI();
	pGUI->UpdateHealth(3); // resetss health
	pCharSprite->SetSpriteSkin("Player.png");
	pC->AddPlayer(player, *this);
	SetPosition(x, y, z);
	SVector2D<float> playerPos = pCharSprite->GetPosition2D();
	pCursor = new CWorldSprite("Crosshair.png", { playerPos.x, playerPos.y, G_SPRITE_LAYER_Z_POS[ESpriteLayers::UI] }, BLEND_CUTOUT);
	pTLEngine->StartMouseCapture();

	// bullet setup
	newBullet = new bulletSetup;
	newBullet->spriteFileName = "QuickBullet.png";
	newBullet->BulletTimeMax = 3.0f;
	newBullet->Speed = 1.5f;
	newBullet->team = EPlayers::PlayerTeam;
}

CPlayer::~CPlayer()
{
	delete pCursor;
}

void CPlayer::Update()
{
	// iframes
	if (mIFrames > 0.0f)
		mIFrames -= *pFrameTimer;

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
		
		// damage
		if (mIFrames <= 0.0f)
		{
			for (int i = 0; i < pBullets->size(); i++)
			{
				CBullet* check = pBullets->at(i);
				// if valid,		if enemy,							if touching
				if (check != NULL && check->returnTeam() == EnemyTeam && (check->GetPos2D() - pCharSprite->GetPosition2D()).Magnitude() <= check->getSize())
				{
					check->Remove();
					ChangeHealth(-1);
				}
			}
		}

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
	if (*pFrameTimer < 1.0f)
	{
		pCursor->MoveX(pTLEngine->GetMouseMovementX() * *pFrameTimer);
		pCursor->MoveY(-pTLEngine->GetMouseMovementY() * *pFrameTimer);
	}

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
	pC->SetGameState(EGameState::GameOver);
}

void CPlayer::ChangeHealth(int change)
{
	if (!mCheatGod || mRollCurrent <= 0.0f && mIFrames <= 0.0f)
	{
		pGUI->TakeDamage(-change);
		CCharacter::ChangeHealth(change);
		mIFrames = mIFRAMES_MAX;
	}
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
	newBullet->spawnPos = GetPos3D();
	SVector2D<float> vec = pCursor->GetPosition2D() - pCharSprite->GetPosition2D();
	newBullet->travelVector = vec.Normalised();

	// create bullet
	new CBullet(*newBullet);

	// fire timer
	mFireTimeCurrent = mFireTimeMax;
}
