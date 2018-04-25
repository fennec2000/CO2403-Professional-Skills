// SMapData.h 11-03-2018
// William John Atkin WJAtkin@UCLan.ac.uk
#include "BUILD_ORDER.h"
#pragma once

struct SMapData
{
	SMapData();
	~SMapData();

	bool mMapDataValid = true;
	SVector2D<int> mWinPosition;

	vector<vector<ETileType>> mTileMap;
	vector<vector<ESpawnTypes>> mSpawnerMap;
	vector<vector<bool>> mCollisionMap;
	vector<SRoomData> mRoomData;
};