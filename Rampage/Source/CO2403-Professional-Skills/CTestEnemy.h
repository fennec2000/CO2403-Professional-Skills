#pragma once
#include "BUILD_ORDER.h"

class CTestEnemy : public CEnemy
{
private:
	CAudio * gunSound;
	const int POINTS = 5;
	bool isActive = false;
	bool shot = false;
	float mMoveSpeed = 0.25f;
	float bulletTimer = 0.0f;
	const float MAX_BULLET_TIMER = 2.5f;
	const int MaxHealth = 1;
	int currentHealth = 1;
	float spriteSizeX = 0.8f;
	float spriteSizeY = 0.8f;

public:
	CTestEnemy(float x, float y, float z, bool activate);
	~CTestEnemy();

	bool EUpdate();
	void Update();
	void Death();
	void toggleActive() { isActive = !isActive; };
	void Shoot();
	void Hit();
	SVector2D<float> blorp() { return pCharSprite->GetPosition2D(); };
};