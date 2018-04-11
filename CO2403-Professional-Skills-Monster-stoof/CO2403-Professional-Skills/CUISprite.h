// CUISprite.h 12-02-2018
// William John Atkin WJAtkin@UCLan.ac.uk


#pragma once
#include "BUILD_ORDER.h"

class CUISprite : protected SBaseSprite
{
public:
	// Constructers
	CUISprite(const char* pSpriteName, SVector3D<float> position);
	CUISprite(const char* pSpriteName, SVector2D<float> position);
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
};
