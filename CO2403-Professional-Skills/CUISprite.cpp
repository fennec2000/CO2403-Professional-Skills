#include "BUILD_ORDER.h"

CUISprite::CUISprite(tle::I3DEngine* pEngine, const char* pSpriteName, SVector3D<float> position) : CBaseSprite(pEngine)
{

}

CUISprite::CUISprite(tle::I3DEngine* pEngine, const char* pSpriteName, SVector2D<float> position) : CBaseSprite(pEngine)
{

}

CUISprite::~CUISprite() { }