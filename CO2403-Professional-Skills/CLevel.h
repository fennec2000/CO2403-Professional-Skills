// CLevel.h 20-02-2018
// William John Atkin WJAtkin@UCLan.ac.uk

#pragma once
#include "BUILD_ORDER.h"

class CLevel
{
public:
	static void LoadLevelFromMapFile(const char* pFilePath);

	static SVector2D<float> GetSpawnPos();

private:
	CLevel();
	~CLevel();

	static void GenerateLevel();
	static void ReadFileToTileMap(const char* pFilePath);

	static vector<vector<ETileType>*>* mTileMap;
	static vector<CWorldSprite*>* mWorldSprites;

	static SVector2D<float>* spawnPos;
};
