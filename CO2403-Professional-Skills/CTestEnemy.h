#pragma once
#include "BUILD_ORDER.h"

class CTestEnemy : protected CEnemy
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
							
		bool EUpdate();
		void Death();
		void toggleActive() { isActive = !isActive; };
		void Shoot();

		void ChangeHealth(int change) { CCharacter::ChangeHealth(change); };

		SVector2D<float> GetPos2D() { return pCharSprite->GetPosition2D(); };
};