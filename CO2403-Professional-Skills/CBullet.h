#pragma once
#include "BUILD_ORDER.h"

struct bulletSetup
{
	string spriteFileName = "QuickBullet.png";
	SVector3D<float> spawnPos = { 0.0f, 0.0f, G_SPRITE_LAYER_Z_POS[ESpriteLayers::Enemy] };
	SVector2D<float> travelVector = { 1.0f, 1.0f };
	float BulletTimeMax = 0.5f;
	float Speed = 1.5f;
};

class CBullet
{
private:
	CCore * pC;
	CWorldSprite* pCharSprite;
	float* pFrameTimer;
	SVector2D<float> mVector = { 0, 0 };
	float mBulletTimerMax = 0.5f;
	float mBulletTimerCurrent = 0.0f;
	float mMoveSpeed = 1.5f;


public:
	CBullet(bulletSetup givenSetup);
	~CBullet();
	void Update();
};
