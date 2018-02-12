#pragma once
#include "BUILD_ORDER.h"

class CWorldSprite : public CBaseSprite
{
public:
	CWorldSprite(tle::I3DEngine* pEngine, const char* pSpriteName, SVector3D<float> position);
	CWorldSprite(tle::I3DEngine* pEngine, const char* pSpriteName, SVector2D<float> position);
	~CWorldSprite();

private:

};

