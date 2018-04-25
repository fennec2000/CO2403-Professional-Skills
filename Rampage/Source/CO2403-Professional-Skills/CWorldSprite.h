// CWorldSprite.h 12-02-2018
// William John Atkin WJAtkin@UCLan.ac.uk
#pragma once
#include "BUILD_ORDER.h"

class CWorldSprite : protected SBaseSprite
{
public:
	// Constructers
	CWorldSprite();
	CWorldSprite(const char* pSpriteName, SVector3D<float> position, ESpriteBlend blending = BLEND_NORMAL);
	CWorldSprite(const char* pSpriteName, SVector2D<float> position, ESpriteBlend blending = BLEND_NORMAL);
	// Destructers
	~CWorldSprite();

	// Constructs the sprite
	void ConstructSprite(const char* pSpriteName, SVector3D<float> position, ESpriteBlend blending = BLEND_NORMAL);

	// Lookat functions
	void LookAt(tle::ISceneNode* target);
	void LookAt(CWorldSprite* target);
	void LookAt(SVector3D<float> target);
	void LookAt(float fX, float fY, float fZ);

	// For sprite movement
	// By translation
	void Move(SVector3D<float> moveAmount);
	void Move(SVector2D<float> moveAmount);
	void MoveX(float moveAmount);
	void MoveY(float moveAmount);
	void MoveZ(float moveAmount);
	// By setting
	void SetPosition(SVector3D<float> moveAmount);
	void SetPosition(SVector2D<float> moveAmount);
	void SetX(float newX);
	void SetY(float newY);
	void SetZ(float newZ);
	// By resetting
	void ResetPosition();

	// By rotation
	void RotateZ(float amount);
	void ResetZRot();

	// Resizing
	void ResizeSprite(float scalar);
	void ResizeX(float scalar);
	void ResizeY(float scalar);

	// Getters
	SVector3D<float> GetPosition3D();
	SVector2D<float> GetPosition2D();
	float GetX();
	float GetY();
	float GetZ();

	// Spirte utills
	void SetSpriteSkin(const char* pSpriteName);

protected:
	tle::IModel* mpSpriteModel;
	
	ESpriteBlend blendingUsed;

	// Normal model
	static int mNormalInstanceCount;
	static tle::IMesh* mpNormalMesh;
	// Cutout model
	static int mCutoutInstanceCount;
	static tle::IMesh* mpCutoutMesh;
	// Multi model
	static int mMultiInstanceCount;
	static tle::IMesh* mpMultiMesh;

	// Names of the .x models for the sprites in diffrent modes
	const char* SPRITE_WORLD_MODEL = "quad.x";
	const char* SPRITE_WORLD_MODEL_CUTOUT = "quad-cutout.x";
	const char* SPRITE_WORLD_MODEL_MULTI = "quad-mul.x";
};

