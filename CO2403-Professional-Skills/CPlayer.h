#pragma once
#include "CCharacter.h"

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
	CPlayer();
	CPlayer(float x, float y, float z);
	~CPlayer();

	// public functions
	void Update();
};

