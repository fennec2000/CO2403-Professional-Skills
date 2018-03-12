#pragma once
#include "BUILD_ORDER.h"

class CTestEnemy : protected CCharacter
{
private:

		bool isActive = false;
		bool shot = false;
		CEProjectile * bullet;
		float mMoveSpeed = 0.5f;
		float mShootTimerMax = 1.0f;
		float mShootTimerCurrent = 0.0f;
public:
		CTestEnemy();
		CTestEnemy(float x, float y, float z, bool activate);
		~CTestEnemy();
							
		void Update();
		void Death();
		void toggleActive() { isActive = !isActive; };
		void Shoot();
};