// CLevel.h 20-02-2018
// William John Atkin WJAtkin@UCLan.ac.uk

#pragma once
#include "BUILD_ORDER.h"

class CLevel
{
public:
	CLevel();
	~CLevel();

	void LoadLevelFromMapFile(const char* pFilePath);
	SVector2D<float> GetSpawnPos();

	ETileType GetTile(int x, int y);
	ETileType GetTile(SVector2D<int> position);
	ETileType GetTile(SVector2D<float> position);

private:

	void GenerateLevel();
	void ReadFileToTileMap(const char* pFilePath);
	void ClearLevel();

	vector<vector<ETileType>*>* mTileMap;
	vector<CWorldSprite*>* mWorldSprites;

	SVector2D<float> mSpawnPos;
};
