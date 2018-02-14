#pragma once
#include "BUILD_ORDER.h"

class CPlayer : protected CCharacter
{
private:
	// data
	// keybindings
	EKeyCode mPlayerMoveUp = EKeyCode::Key_Numpad8;
	EKeyCode mPlayerMoveLeft = EKeyCode::Key_Numpad4;
	EKeyCode mPlayerMoveDown = EKeyCode::Key_Numpad5;
	EKeyCode mPlayerMoveRight = EKeyCode::Key_Numpad6;

	float mMoveSpeed = 1.0f;

	// functions
	void InputCheck();

public:
	CPlayer(EPlayers player);
	CPlayer(EPlayers player, float x, float y, float z);
	~CPlayer();

	// public functions
	void Update();
	float GetX() { return mpCharSprite->GetX(); };
	float GetY() { return mpCharSprite->GetY(); };
};

