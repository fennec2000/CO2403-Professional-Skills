#pragma once
#include "BUILD_ORDER.h"

class CTestEnemy : protected CEnemy
{
private:

		bool isActive = false;
		bool shot = false;
		CEProjectile * bullet;
		float mMoveSpeed = 0.5f;
		SVector2D<float> mFireVector;	
		float bulletTimer = 0.0f;
		const float MAX_BULLET_TIMER = 0.5f;
		
public:
		CTestEnemy();
		CTestEnemy(float x, float y, float z, bool activate);
		~CTestEnemy();
							
		void Update();
		void Death();
		void toggleActive() { isActive = !isActive; };
		void Shoot();
};