#pragma once
#include "BUILD_ORDER.h"

class CEnemyShotgun : public CEnemy
{
private:

	bool isActive = false;
	bool shot = false;
	CEProjectile * bullet;
	float mMoveSpeed = 0.25f;
	float bulletTimer = 0.0f;
	float bulletSpreadAngle = 15;
	const float MAX_BULLET_TIMER = 2.5f;
	const float DISTANCE_TO_KEEP = 5.0f;

public:
	CEnemyShotgun(float x, float y, float z, bool activate);
	~CEnemyShotgun();

	void Update();
	void Death();
	void toggleActive() { isActive = !isActive; };
	void Shoot();
	SVector2D<float> blorp() { return pCharSprite->GetPosition2D(); };
};