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

	bool GetTileCollision(int x, int y);
	bool GetTileCollision(SVector2D<int> position);

private:

	void GenerateLevel();
	void ReadFileToTileMap(const char* pFilePath);
	void ClearLevel();

	vector<vector<ETileType>*>* mTileMap;
	vector<vector<bool>*>* mCollisionMap;
	vector<CWorldSprite*>* mWorldSprites;

	SVector2D<float> mSpawnPos;
};
