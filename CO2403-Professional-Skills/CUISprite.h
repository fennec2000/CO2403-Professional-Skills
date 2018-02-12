#pragma once
#include "BUILD_ORDER.h"

class CUISprite : public CBaseSprite
{
public:
	// Constructers
	CUISprite(tle::I3DEngine* pEngine, const char* pSpriteName, SVector3D<float> position);
	CUISprite(tle::I3DEngine* pEngine, const char* pSpriteName, SVector2D<float> position);
	// Destructers
	~CUISprite();

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

	// Getters
	SVector3D<float> GetPosition3D();
	SVector2D<float> GetPosition2D();
	float GetX();
	float GetY();
	float GetZ();

private:

	// This UIs sprite
	tle::ISprite* mpSprite;

	// Z position that the UI will default to if one
	// is not specifiyed
	const float DEFAULT_Z_POS = 0.5f;
};
