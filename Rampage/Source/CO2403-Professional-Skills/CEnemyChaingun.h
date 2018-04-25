#pragma once
#include "BUILD_ORDER.h"

class CEnemyChaingun : public CEnemy
{
private:
	CAudio* gunSound;
	const int POINTS = 10;
	const int DROP_SHOTGUN_CHANCE = 20;	// out of 100
	bool isActive = false;
	bool isShooting = false;
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
	const int MaxHealth = 1;
	int currentHealth = 1;
	float spriteSizeX = 0.8f;
	float spriteSizeY = 0.8f;


public:
	CEnemyChaingun();
	CEnemyChaingun(float x, float y, float z, bool activate);
	~CEnemyChaingun();

	bool EUpdate();
	void Update();
	void Death();
	void toggleActive() { isActive = !isActive; };
	void Shoot();
	void Hit();
	SVector2D<float> blorp() { return pCharSprite->GetPosition2D(); };
};