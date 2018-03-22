#pragma once
#include "BUILD_ORDER.h"

class CPlayer;

struct bulletSetup
{
	string spriteFileName = "UglyTile.png";
	SVector3D<float> spawnPos = { 0.0f, 0.0f, G_SPRITE_LAYER_Z_POS[ESpriteLayers::Enemy] };
	SVector2D<float> travelVector = { 1.0f, 1.0f };
	float spriteRadius = 1.0f;
	float bulletTimeMax = 0.5f;
	float Speed = 1.5f;
	int bulletDamage = 1.0f;
	EPlayers team = EPlayers::EnemyTeam;
};

class CBullet
{
private:
	CCore* pC;
	CWorldSprite* pCharSprite;
	float* pFrameTimer;
	SVector2D<float> mVector = { 0, 0 };
	float mRadius = 1.0f;
	float mBulletTimerMax = 0.5f;
	float mBulletTimerCurrent = 0.0f;
	float mMoveSpeed = 1.5f;
	int mBulletDamage = 1.0f;
	EPlayers mTeam = EPlayers::EnemyTeam;

public:
	CBullet(bulletSetup &givenSetup);
	~CBullet();
	void Update();
};

