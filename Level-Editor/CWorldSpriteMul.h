// CWorldSpriteMul.h 11-03-2018
// William John Atkin WJAtkin@UCLan.ac.uk
#pragma once
#include "BUILD_ORDER.h"

class CWorldSpriteMul : public CWorldSprite
{
public:
	// Constructers
	CWorldSpriteMul(const char* pSpriteName, SVector3D<float> position);
	CWorldSpriteMul(const char* pSpriteName, SVector2D<float> position);
	// Destructers
	~CWorldSpriteMul();

private:
	void SetUp();

	static int mInstanceCountMul;
	static tle::IMesh* mpMeshMul;

	const char* SPRITE_MODEL_NAME = "quad-mul.x";
};

