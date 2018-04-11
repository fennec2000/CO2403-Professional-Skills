#pragma once
#include "BUILD_ORDER.h"

class CEnemyChaingun : public CEnemy
{
private:

	bool isActive = false;
	bool isShooting = false;
	CEProjectile * bullet;
	float mMoveSpeed = 0.5f;
	SVector2D<float> mFireVector;
	float bulletTimer = 0.0f;
	float chaingunFireTime = 0.0f;
	float currentRevTime = 0.0f;
	float chaingunMaxRevTime = 0.5f;
	float CHAINGUN_BULLET_DISPLACEMENT = 0.1f;
	const float MAX_BULLET_TIMER = 5.0f;
	const float MAX_CHAINGUN_FIRE_TIME = 10.0f;
	const float MIN_CHAINGUN_BULLET_TIME = 0.05f;
	const float CHAINGUN_REV_DECREMENT = 0.05f;
	const float MAXC_HAINGUN_DISPLACEMENT = 3.0f;


public:
	CEnemyChaingun();
	CEnemyChaingun(float x, float y, float z, bool activate);
	~CEnemyChaingun();

	void Update();
	void Death();
	void toggleActive() { isActive = !isActive; };
	void Shoot();
};