// CWorldSprite.h 12-02-2018
// William John Atkin WJAtkin@UCLan.ac.uk

#pragma once
#include "BUILD_ORDER.h"

class CWorldSprite : public CBaseSprite
{
public:
	// Constructers
	CWorldSprite(const char* pSpriteName, SVector3D<float> position);
	CWorldSprite(const char* pSpriteName, SVector2D<float> position);
	// Destructers
	~CWorldSprite();

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

	// Getters
	SVector3D<float> GetPosition3D();
	SVector2D<float> GetPosition2D();
	float GetX();
	float GetY();
	float GetZ();

	// Spirte utills
	void SetSpriteSkin(const char* pSpriteName);

private:
	tle::IModel* mpSpriteModel;
	
	static int mInstanceCount;
	static tle::IMesh* mpMesh;

	const char* SPRITE_WORLD_MODEL = "quad.x";
};

