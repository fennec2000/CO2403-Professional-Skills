#pragma once
#include "BUILD_ORDER.h"

class CTestEnemy : protected CCharacter
{
private:
	// data
	bool isActive;

	float mMoveSpeed = 0.5f;

	// functions

public:
	CTestEnemy();
	CTestEnemy(float x, float y, float z, bool activate);
	~CTestEnemy();

	// public functions

	void Update();
};