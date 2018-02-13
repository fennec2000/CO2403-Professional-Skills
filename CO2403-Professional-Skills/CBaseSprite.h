// CBaseSprite.h 10-02-2018
// William John Atkin WJAtkin@UCLan.ac.uk

#pragma once
#include "BUILD_ORDER.h"

class CBaseSprite
{
protected:
	SVector3D<float> mOrigin;
	SVector3D<float> mOffset;

	// Z position that the UI will default to if one
	// is not specifiyed
	const float DEFAULT_Z_POS = 0.5f;

	// Putting the constructer as protected prevents an instance
	// of this object ever being created
	CBaseSprite();

};
