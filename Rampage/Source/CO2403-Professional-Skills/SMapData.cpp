// SMapData.h 11-03-2018
// William John Atkin WJAtkin@UCLan.ac.uk
#include "BUILD_ORDER.h"

SMapData::SMapData()
{
	// Inits the tileMap
	for (int yPos = 0; yPos < CLevel::MAP_MAX_SIZE.y; yPos++)
	{
		vector<ETileType> line;
		for (int xPos = 0; xPos < CLevel::MAP_MAX_SIZE.x; xPos++)
		{
			line.push_back(NO_TILE);
		}
		mTileMap.push_back(line);
	}

	// Inits the sapwner map
	for (int yPos = 0; yPos < CLevel::MAP_MAX_SIZE.y; yPos++)
	{
		vector<ESpawnTypes> line;
		for (int xPos = 0; xPos < CLevel::MAP_MAX_SIZE.x; xPos++)
		{
			line.push_back(SPAWN_NOTHING);
		}
		mSpawnerMap.push_back(line);
	}

	// Inits the collision map
	for (int yPos = 0; yPos < CLevel::MAP_MAX_SIZE.y; yPos++)
	{
		vector<bool> line;
		for (int xPos = 0; xPos < CLevel::MAP_MAX_SIZE.x; xPos++)
		{
			line.push_back(false);
		}
		mCollisionMap.push_back(line);
	}
}

SMapData::~SMapData()
{

}