#pragma once
#include "BUILD_ORDER.h"
// This class has the base functions that both the player and enemies have

class CEProjectile : protected CCharacter
{
private:
	// data
	float eMoveSpeed = 2.5f;
	float maxLifetime = 3.0f;
	float lifetime = 0.0f;

	// functions

public:
	CEProjectile();
	CEProjectile(float x, float y, float z);
	~CEProjectile();

	// public functions

	void Update();
};