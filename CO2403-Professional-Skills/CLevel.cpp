// CLevel.h 20-02-2018
// William John Atkin WJAtkin@UCLan.ac.uk

#include "BUILD_ORDER.h"

const SVector2D<int> CLevel::MAP_MAX_SIZE = { 128, 128 };

CLevel::CLevel() 
{ 
	// Fills the sprite level tiles with empty sprites
	for (int i = 0; i < MAP_MAX_SIZE.x; i++)
	{
		mWorldSprites.push_back(new vector<CWorldSprite*>);
		for (int j = 0; j < MAP_MAX_SIZE.y; j++)
		{
			mWorldSprites[i]->push_back(nullptr);
		}
	}
}

CLevel::~CLevel() 
{ 
	UnloadLevel();
}

void CLevel::Update()
{
	for (int i = 0; i < levelEnemies.size(); i++)
	{	
			bool meow = levelEnemies[i]->EUpdate();	
			if (meow)
			{
				levelEnemies.erase(i + levelEnemies.begin());
			}
	}
}

SVector2D<float> CLevel::GetSpawnPos()
{
	return mSpawnPos;
}

ETileType CLevel::GetTile(int x, int y)
{
	return mMapData.mTileMap[y].at(x);
}

ETileType CLevel::GetTile(SVector2D<int> position)
{
	return mMapData.mTileMap[position.y].at(position.x);
}

ETileType CLevel::GetTile(SVector2D<float> position)
{
	return mMapData.mTileMap.at(static_cast<int>(position.y)).at(static_cast<int>(position.x));
}

bool CLevel::GetTileCollision(int x, int y)
{
	return mCollisionMap->at(y)->at(x);
}

bool CLevel::GetTileCollision(SVector2D<int> position)
{
	return mCollisionMap->at(position.y)->at(position.x);
}

void CLevel::LoadLevel(const char* filePath)
{
	UnloadLevel();
	mMapData = CMapIO::ReadMapFile(filePath);
	GenerateLevel();

	// Checks through the spawners and does appropirate things
	for (int yPos = 0; yPos < CLevel::MAP_MAX_SIZE.y; yPos++)
	{
		for (int xPos = 0; xPos < CLevel::MAP_MAX_SIZE.x; xPos++)
		{
			switch (mMapData.mSpawnerMap[yPos].at(xPos))
			{
			case SPAWN_PLAYER:
				mSpawnPos = { static_cast<float>(xPos), static_cast<float>(yPos) };
				break;
			case SPAWN_ENEMY:
				levelEnemies.push_back(new CEnemyChaingun(static_cast<float>(xPos), static_cast<float>(yPos), 0.0f, true));
				break;
			}
		}
	}
}

void CLevel::GenerateLevel()
{
	for (int yPos = 0; yPos < MAP_MAX_SIZE.y; yPos++)
	{
		for (int xPos = 0; xPos < MAP_MAX_SIZE.x; xPos++)
		{
			// Check if there is a tile to display
			if (mMapData.mTileMap[yPos].at(xPos) != NO_TILE)
			{
				// Create the sprite
				switch (mMapData.mTileMap[yPos].at(xPos))
				{
				case WALL:
					GenerateSprite(TileNames::FULL_WALL, { xPos, yPos });
					break;
				case FLOOR:
					GenerateSprite(TileNames::FLOOR, { xPos, yPos });
					break;
				case WALL_WITH_SIDE:
					GenerateSprite(TileNames::WALL_SIDE, { xPos, yPos });
					break;
				case WALL_WITH_SIDE_FLIPPED_Y:
					GenerateSprite(TileNames::WALL_SIDE_FLIPPED_Y, { xPos, yPos });
					break;
				}
			}
		}
	}
}

void CLevel::UnloadLevel()
{
	// Reset all the data
	mMapData = SMapData();

	// Cleans the sprites
	for (int yPos = 0; yPos < CLevel::MAP_MAX_SIZE.y; yPos++)
	{
		for (int xPos = 0; xPos < CLevel::MAP_MAX_SIZE.x; xPos++)
		{
			if (mWorldSprites.at(yPos)->at(xPos) != nullptr)
			{

				delete mWorldSprites.at(yPos)->at(xPos);
				mWorldSprites.at(yPos)->at(xPos) = nullptr;
			}
		}
	}

	// remove enemies
	int size = levelEnemies.size();
	while (levelEnemies.size() > 0)
	{
		delete levelEnemies[levelEnemies.size() - 1];
		levelEnemies[levelEnemies.size() - 1] = nullptr;
		levelEnemies.pop_back();
	}
}

void CLevel::GenerateSprite(const char* pSpriteName, SVector2D<int> position)
{
	if (mWorldSprites[position.x]->at(position.y) == nullptr)
	{
		// Generate the sprite
		mWorldSprites[position.x]->at(position.y) = new CWorldSprite(pSpriteName, { (float)position.x, (float)position.y, G_SPRITE_LAYER_Z_POS[ESpriteLayers::Floor] });
	}
	else
	{
		// Change the existing skin
		mWorldSprites[position.x]->at(position.y)->SetSpriteSkin(pSpriteName);
		mWorldSprites[position.x]->at(position.y)->ResetZRot();
	}
}