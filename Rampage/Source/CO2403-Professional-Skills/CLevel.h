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

	SVector2D<int> GetWinPos();

	// Map genration and unloading
	void LoadLevel(const char* filePath);
	vector<CEnemy*> getEnemies() { return levelEnemies; };
	void UnloadLevel();

	int currentRoom = -1;

	static const SVector2D<int> MAP_MAX_SIZE;

private:

	void GenerateLevel();
	void StartRoom(int roomNo);
	void ClearRoom();

	vector<CEnemy*> levelEnemies;

	SMapData mMapData;
	vector<vector<bool>*>* mCollisionMap;
	vector<vector<CWorldSprite*>*> mWorldSprites;
	vector<vector<CAnimatedWorldSprite*>*> mAnimWorldSprites;

	SVector2D<float> mSpawnPos;

	void GenerateSprite(const char* pSpriteName, SVector2D<int> position);
	void GenerateAnimatedWorldSprite(vector<const char*> spriteList, SVector2D<int> position);
};
