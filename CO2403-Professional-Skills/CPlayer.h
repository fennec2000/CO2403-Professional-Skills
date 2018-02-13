#pragma once
#include "CCharacter.h"

class CPlayer : public CCharacter
{
public:
	CPlayer();
	CPlayer(float x, float y, float z);
	~CPlayer();

	// public functions
	void Update();
};

