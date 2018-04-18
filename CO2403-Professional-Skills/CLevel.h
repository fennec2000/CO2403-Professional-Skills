// CLevel.h 20-02-2018
// William John Atkin WJAtkin@UCLan.ac.uk

#pragma once
#include "BUILD_ORDER.h"

class CEnemy;

class CLevel
{
public:
	CLevel();
	~CLevel();

	void Update();

	SVector2D<float> GetSpawnPos();

	ETileType GetTile(int x, int y);
	ETileType GetTile(SVector2D<int> position);
	ETileType GetTile(SVector2D<float> position);

	bool GetTileCollision(int x, int y);
	bool GetTileCollision(SVector2D<int> position);

	// Map genration and unloading
	void LoadLevel(const char* filePath);
	void UnloadLevel();

	static const SVector2D<int> MAP_MAX_SIZE;

private:

	void GenerateLevel();

	vector<CEnemy*> levelEnemies;

	SMapData mMapData;
	vector<vector<bool>*>* mCollisionMap;
	vector<vector<CWorldSprite*>*> mWorldSprites;

	SVector2D<float> mSpawnPos;

	void GenerateSprite(const char* pSpriteName, SVector2D<int> position);

};
