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
	pTLEngine->StartMouseCapture();
	pCamera = pC->GetCamera();
	pLevel = pC->GetLevel();
	pBullets = pC->GetBullets();
	pGUI = pC->GetGUI();
	pGUI->UpdateHealth(3); // resets health
	pCharSprite->SetSpriteSkin(PlayerSkins[0]);
	pC->AddPlayer(player, *this);
	pPowerUps = &pC->pPowerUps;
	SetPosition(x, y, z);
	SVector2D<float> playerPos = pCharSprite->GetPosition2D();
	pCursor = new CWorldSprite("Crosshair.png", { playerPos.x, playerPos.y, G_SPRITE_LAYER_Z_POS[ESpriteLayers::UI] }, BLEND_CUTOUT);
	mFirstRun = true;

	// bullet setup
	newBullet = new bulletSetup;
	newBullet->spriteFileName = "QuickBullet.png";
	newBullet->BulletTimeMax = 3.0f;
	newBullet->Speed = 3.0f;
	newBullet->team = EPlayers::PlayerTeam;

	LoadSounds();
}

CPlayer::~CPlayer()
{
	FreeSounds();
	delete pCursor;
}

void CPlayer::Update()
{
	// iframes
	if (mIFrames > 0.0f)
	{
		mIFrames -= *pFrameTimer;
		if (mIFrames <= 0.0f)
		{
			mIFrames = 0.0f;
			pCharSprite->SetSpriteSkin(PlayerSkins[0]);
		}
	}

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
		pCharSprite->LookAt(pCursor->GetX(), pCursor->GetY(), pCharSprite->GetZ());
	}

	// powerup check
	for (auto it = pPowerUps->begin(); it != pPowerUps->end();)
	{
		if (*it != NULL && ((*it)->pWorldSprite->GetPosition2D() - pCharSprite->GetPosition2D()).Magnitude() < ITEM_PICKUP_RANGE)
		{
			SPowerUpInfo itemInfo = (*it)->GetEffect();
			if (itemInfo.power == EPowerUps::GiveShotgun)
			{
				mShotgunAmmo += itemInfo.strenght; // add ammo
				pGUI->SetWeaponIcon(EWeapons::Shotgun); // update gui
				playerSounds[EPlayerSounds::PlayerFireSound] = gunSounds[EGunSounds::ShotgunSound];
			}
			delete (*it);
			it = pPowerUps->erase(it);
		}
		if (it != pPowerUps->end()) ++it;
	}

	// cooldowns
	if (mFireTimeCurrent > 0.0f)
		mFireTimeCurrent -= *pFrameTimer;

	// update camera
	SVector2D<float> playerPos = pCharSprite->GetPosition2D();
	pCamera->SetPosition(playerPos.x + mCAMERA_OFFSET.x, playerPos.y + mCAMERA_OFFSET.y, mCAMERA_OFFSET.z);

	mRenderedFirstFrame = true;
}

void CPlayer::InputCheck()
{
	{
		pCursor->MoveY(-pTLEngine->GetMouseMovementY() * *pFrameTimer);
	}
	else
	{
		// Set the cursor just over the player
		pCursor->SetPosition({ GetX() + 1.0f, GetY() });

		// get the mouse movement but not do anything with it so that
		// tl resets it
		pTLEngine->GetMouseMovementX();
		pTLEngine->GetMouseMovementY();
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

			// play roll sound
			playerSounds[EPlayerSounds::PlayerRoll]->Play();
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
		pCharSprite->SetSpriteSkin(PlayerSkins[1]);
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

	// play sound
	playerSounds[EPlayerSounds::PlayerFireSound]->Play();

	// shotgun
	if (mShotgunAmmo > 0)
	{
		// set up spread
		float firingAngle = BULLET_SPREAD_ANGLE * 3.14 / 180;
		SVector2D<float> vec2;
		SVector2D<float> vec3;
		vec2.x = newBullet->travelVector.x * cos(firingAngle) - newBullet->travelVector.y * sin(firingAngle);
		vec2.y = newBullet->travelVector.x * sin(firingAngle) + newBullet->travelVector.y * cos(firingAngle);
		vec3.x = newBullet->travelVector.x * cos(-firingAngle) - newBullet->travelVector.y * sin(-firingAngle);
		vec3.y = newBullet->travelVector.x * sin(-firingAngle) + newBullet->travelVector.y * cos(-firingAngle);

		// fire
		newBullet->travelVector = vec2;
		new CBullet(*newBullet);
		newBullet->travelVector = vec3;
		new CBullet(*newBullet);

		// decrement ammo
		--mShotgunAmmo;
		if (mShotgunAmmo <= 0)
		{
			mShotgunAmmo = 0; 
			pGUI->SetWeaponIcon(EWeapons::Default);
			playerSounds[EPlayerSounds::PlayerFireSound] = gunSounds[EGunSounds::PistolSound];
		}
	}

	// fire timer
	mFireTimeCurrent = mFireTimeMax;
}

void CPlayer::LoadSounds()
{
	// guns sounds
	gunSounds[EGunSounds::PistolSound] = new CAudio("Media\\Sound\\PistolSound.wav", false);
	gunSounds[EGunSounds::ShotgunSound] = new CAudio("Media\\Sound\\ShotgunSound.wav", false);

	// player sounds
	playerSounds[EPlayerSounds::PlayerRoll] = new CAudio("Media\\Sound\\Roll.wav", false);
	playerSounds[EPlayerSounds::PlayerFireSound] = gunSounds[EGunSounds::ShotgunSound];
}

void CPlayer::FreeSounds()
{
	delete playerSounds[EPlayerSounds::PlayerRoll];

	delete gunSounds[EGunSounds::ShotgunSound];
	delete gunSounds[EGunSounds::PistolSound];
}
