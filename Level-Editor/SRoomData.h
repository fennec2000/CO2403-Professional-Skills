// SRoomData.h 21-03-2018
// William John Atkin WJAtkin@UCLan.ac.uk
#include "BUILD_ORDER.h"
#pragma once

struct SRoomData
{
	SVector2D<int> mMinPos;
	SVector2D<int> mMaxPos;

	vector<SVector2D<int>> mEnemyPositions;
};