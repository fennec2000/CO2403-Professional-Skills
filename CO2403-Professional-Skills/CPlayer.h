#pragma once
#include "BUILD_ORDER.h"

class CPlayer : protected CCharacter
{
private:
	// data
	CWorldSprite* pCursor;
	ICamera* pCamera;
	CLevel* pLevel;

	// keybindings
	EKeyCode mPlayerMoveUp = EKeyCode::Key_W;
	EKeyCode mPlayerMoveLeft = EKeyCode::Key_A;
	EKeyCode mPlayerMoveDown = EKeyCode::Key_S;
	EKeyCode mPlayerMoveRight = EKeyCode::Key_D;
	EKeyCode mPlayerRoll = EKeyCode::Key_Space;
	EKeyCode mPlayerFire = EKeyCode::Mouse_LButton;

	const SVector3D<float> mCAMERA_OFFSET = { 0.0f, 0.0f, -10.0f };
	float mMoveSpeed = 2.0f;
	SVector2D<float> mOldPos;
	SVector2D<float> mMovement;
	const SVector2D<float> mCharSize = { 1.0f, 1.0f }; // x, y
	int mScreenSize[2]; // 0 - height, 1 - width
	float mRotationCurrent = 0.0f;

	// roll
	SVector2D<float> mRollVector;
	const float mROLL_DISTANCE_MAX = 3.0f;
	const float mROLL_SPEED = 5.0f;
	float mRollCurrent;

	// cheats
	bool mCheatGod = false;

	// functions
	void InputCheck();
	void Move(SVector2D<float> movement);
	bool CollisionCheck(SVector2D<float> pos);

public:
	CPlayer(EPlayers player);
	CPlayer(EPlayers player, float x, float y, float z);
	~CPlayer();

	// public functions
	void Update();
	void Death();
	void ChangeHealth(int change);
	float GetX() { return pCharSprite->GetX(); };
	float GetY() { return pCharSprite->GetY(); };
};

