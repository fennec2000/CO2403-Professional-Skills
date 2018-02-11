#pragma once
#include "BUILD_ORDER.h"

class CBaseSprite
{
protected:
	SVector3D<float> mOrigin;
	SVector3D<float> mOffset;

	tle::I3DEngine* mpEngine;

	// Putting the constructer as protected prevents an instance
	// of this object ever being created
	CBaseSprite(tle::I3DEngine* pEngine);

};
