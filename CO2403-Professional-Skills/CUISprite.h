#pragma once
#include "BUILD_ORDER.h"

class CUISprite : public CBaseSprite
{
public:
	CUISprite(tle::I3DEngine* pEngine, const char* pSpriteName, SVector3D<float> position);
	CUISprite(tle::I3DEngine* pEngine, const char* pSpriteName, SVector2D<float> position);
	~CUISprite();

private:
	tle::ISprite* mpSprite;

};
