// CButtonSprite.h 08-03-2018
// William John Atkin WJAtkin@UCLan.ac.uk
#include "BUILD_ORDER.h"
#pragma once

class CButtonSprite : protected SBaseSprite
{
public:
	CButtonSprite(const char* pSpriteName, const char* pHoverSpriteName, SVector3D<float> position, SVector2D<float> size);
	CButtonSprite(const char* pSpriteName, const char* pHoverSpriteName, SVector2D<float> position, SVector2D<float> size);
	~CButtonSprite();

	bool CheckClick();

private:
	void CalculateColisionBox(SVector2D<float> position, SVector2D<float> size);

	const float HIDE_Z_POS = -1.0f;

	// For changing bettween Sprites
	bool hoverVisable = false; // Flag to prevent unessary code ex
	void ShowHoverSprite();
	void ShowNormalSprite();

	// Collision Parameters
	SVector2D<int> minPos;
	SVector2D<int> maxPos;

	// This UIs sprites
	tle::ISprite* mpNormalSprite;
	tle::ISprite* mpHoverSprite;
};
