#pragma once
#include "BUILD_ORDER.h"

struct bulletSetup;

enum EPlayerSounds { PlayerMoveSound, PlayerFireSound, PlayerRoll, NumOfPlayerSounds };
enum EGunSounds { PistolSound, ShotgunSound, NumOfGunSounds };

class CPlayer : public CCharacter
{
private:
	// data
	CWorldSprite* pCursor;
	ICamera* pCamera;
	CGUI* pGUI;
	vector<CBullet*>* pBullets;
	bool mFirstRun;

	// player skin names
	const char* PlayerSkins[2] = { "Player.png", "PlayerShielded.png" };

	// take damage
	const float mIFRAMES_MAX = 2.0f;
	float mIFrames = 0;
	bool mRenderedFirstFrame = false;

	// keybindings
	EKeyCode mPlayerMoveUp = EKeyCode::Key_W;
	EKeyCode mPlayerMoveLeft = EKeyCode::Key_A;
	EKeyCode mPlayerMoveDown = EKeyCode::Key_S;
	EKeyCode mPlayerMoveRight = EKeyCode::Key_D;
	EKeyCode mPlayerRoll = EKeyCode::Key_Space;
	EKeyCode mPlayerFire = EKeyCode::Mouse_LButton;

	const SVector3D<float> mCAMERA_OFFSET = { 0.0f, 0.0f, -10.0f };
	int mScreenSize[2]; // 0 - height, 1 - width
	SVector2D<float> mMovement;

	// sound
	CAudio* playerSounds[EPlayerSounds::NumOfPlayerSounds];
	CAudio* gunSounds[EPlayerSounds::NumOfPlayerSounds];

	// roll
	SVector2D<float> mRollVector;
	const float mROLL_DISTANCE_MAX = 3.0f;
	const float mROLL_SPEED = 5.0f;
	float mRollCurrent;

	// firing
	float mFireTimeMax = 0.5f;
	float mFireTimeCurrent = 0.0f;
	int mShotgunAmmo = 3;
	const float BULLET_SPREAD_ANGLE = 15.0f;
	bulletSetup* newBullet;

	// items
	vector<CPowerUp*>* pPowerUps;
	const float ITEM_PICKUP_RANGE = 1.0f;
	const int POWERUP_SHOTGUN_ADD_AMMO = 10;

	// cheats
	bool mCheatGod = false;

	// functions
	void InputCheck();
	void Move(SVector2D<float> movement);
	void Death();
	void Shoot();
	void LoadSounds();
	void FreeSounds();

public:
	CPlayer(EPlayers player);
	CPlayer(EPlayers player, float x, float y, float z);
	virtual ~CPlayer();

	// public functions
	void Update();
	void ChangeHealth(int change);
	float GetX() { return pCharSprite->GetX(); };
	float GetY() { return pCharSprite->GetY(); };
	float GetZ() { return pCharSprite->GetZ(); };
	SVector2D<float> GetPos2D() { return pCharSprite->GetPosition2D(); };
	int GetShotgunAmmo() { return mShotgunAmmo; };
};

