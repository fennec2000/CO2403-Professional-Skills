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

	for (int i = 0; i < MAP_MAX_SIZE.x; i++)
	{
		mAnimWorldSprites.push_back(new vector<CAnimatedWorldSprite*>);
		for (int j = 0; j < MAP_MAX_SIZE.y; j++)
		{
			mAnimWorldSprites[i]->push_back(nullptr);
		}
	}
}

CLevel::~CLevel() 
{ 
	UnloadLevel();
}

void CLevel::Update()
{
	// Tests if the player has entered a new room
	CCore* pCore = CCore::GetInstance();
	SVector2D<float> playerPos = pCore->GetPlayer(EPlayers::PlayerTeam)->GetPos2D();

	if (currentRoom == -1)
	{
		bool inRoom = false;
		for (unsigned int i = 0; i < mMapData.mRoomData.size(); i++)
		{
			SVector2D<float> roomMin = { static_cast<float>(mMapData.mRoomData[i].mMinPos.x) + 1.0f,  static_cast<float>(mMapData.mRoomData[i].mMinPos.y) + 1.0f };
			SVector2D<float> roomMax = { static_cast<float>(mMapData.mRoomData[i].mMaxPos.x) - 1.0f,  static_cast<float>(mMapData.mRoomData[i].mMaxPos.y) - 1.0f };
			if (playerPos.x > roomMin.x && playerPos.x < roomMax.x)
			{
				if (playerPos.y > roomMin.y && playerPos.y < roomMax.y)
				{
					// Player is in this room
					// Check to make sure it has not been defeted
					if (!mMapData.mRoomData[i].mRoomCleared)
					{
						inRoom = true;
						StartRoom(i);
						continue;
					}
				}
			}
		}
	}
	else
	{
		// Check if all enemey are dead
		if (levelEnemies.size() == 0)
		{
			ClearRoom();
		}
		else
		{
			// Updates the enemeys in the room
			for (unsigned int i = 0; i < levelEnemies.size(); i++)
			{	
				bool meow = levelEnemies[i]->EUpdate();	
				if (meow)
				{
					levelEnemies.erase(i + levelEnemies.begin());
				}
			}
		}
	}
	
	// Updates animated sprites
	for (int yPos = 0; yPos < CLevel::MAP_MAX_SIZE.y; yPos++)
	{
		for (int xPos = 0; xPos < CLevel::MAP_MAX_SIZE.x; xPos++)
		{
			if (mAnimWorldSprites.at(yPos)->at(xPos) != nullptr)
			{
				mAnimWorldSprites.at(yPos)->at(xPos)->Update();
			}
		}
	}
}

void CLevel::StartRoom(int roomNo)
{
	currentRoom = roomNo;

	// Close doors
	for (unsigned int i = 0; i < mMapData.mRoomData[roomNo].mDoorPositions.size(); i++)
	{
		if (GetTile(mMapData.mRoomData[roomNo].mDoorPositions[i]) == DOOR_OPEN)
		{
			mMapData.mTileMap[mMapData.mRoomData[currentRoom].mDoorPositions[i].y].at(mMapData.mRoomData[currentRoom].mDoorPositions[i].x) = DOOR;
			GenerateSprite(TileNames::DOOR, mMapData.mRoomData[roomNo].mDoorPositions[i]);
		}
		else
		{
			mMapData.mTileMap[mMapData.mRoomData[currentRoom].mDoorPositions[i].y].at(mMapData.mRoomData[currentRoom].mDoorPositions[i].x) = DOOR_ROT;
			GenerateSprite(TileNames::DOOR_ROT, mMapData.mRoomData[roomNo].mDoorPositions[i]);
		}
	}

	// Spawn enemys
	for (int yPos = mMapData.mRoomData[roomNo].mMinPos.y; yPos < mMapData.mRoomData[roomNo].mMaxPos.y; yPos++)
	{
		for (int xPos = mMapData.mRoomData[roomNo].mMinPos.x; xPos < mMapData.mRoomData[roomNo].mMaxPos.x; xPos++)
		{
			switch (mMapData.mSpawnerMap[yPos].at(xPos))
			{
			case SPAWN_ENEMY:
				//levelEnemies.push_back(new CTestEnemy(static_cast<float>(xPos), static_cast<float>(yPos), 0.0f, true));
				break;
			case SPAWN_SHOT_ENEMY:
				levelEnemies.push_back(new CEnemyShotgun(static_cast<float>(xPos), static_cast<float>(yPos), 0.0f, true));
				break;
			case SPAWN_CHAIN_ENEMY:
				levelEnemies.push_back(new CEnemyChaingun(static_cast<float>(xPos), static_cast<float>(yPos), 0.0f, true));
				break;
			case SPAWN_RAND_ENEMY:
				// Do nothing for now
				break;
			}
		}
	}
}

void CLevel::ClearRoom()
{
	// Open the doors
	for (unsigned int i = 0; i < mMapData.mRoomData[currentRoom].mDoorPositions.size(); i++)
	{
		if (GetTile(mMapData.mRoomData[currentRoom].mDoorPositions[i]) == DOOR)
		{
			mMapData.mTileMap[mMapData.mRoomData[currentRoom].mDoorPositions[i].y].at(mMapData.mRoomData[currentRoom].mDoorPositions[i].x) = DOOR_OPEN;
			GenerateSprite(TileNames::DOOR_OPEN, mMapData.mRoomData[currentRoom].mDoorPositions[i]);
		}
		else
		{
			mMapData.mTileMap[mMapData.mRoomData[currentRoom].mDoorPositions[i].y].at(mMapData.mRoomData[currentRoom].mDoorPositions[i].x) = DOOR_ROT_OPEN;
			GenerateSprite(TileNames::DOOR_ROT_OPEN, mMapData.mRoomData[currentRoom].mDoorPositions[i]);
		}
	}

	// Mark this room as clear
	mMapData.mRoomData[currentRoom].mRoomCleared = true;
	currentRoom = -1;
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
				case WALL_SERVER_ANIMATED:
				{
					vector<const char*> spriteList;
					spriteList.push_back("wallServer1.png");
					spriteList.push_back("wallServer2.png");
					spriteList.push_back("wallServer3.png");
					spriteList.push_back("wallServer4.png");
					spriteList.push_back("wallServer5.png");
					spriteList.push_back("wallServer6.png");
					GenerateAnimatedWorldSprite(spriteList, { xPos, yPos });
				}
					break;
				case DOOR:
					mMapData.mTileMap[yPos].at(xPos) = DOOR_OPEN;
					GenerateSprite(TileNames::DOOR_OPEN, { xPos, yPos });
					break;
				case DOOR_ROT:
					mMapData.mTileMap[yPos].at(xPos) = DOOR_ROT_OPEN;
					GenerateSprite(TileNames::DOOR_ROT_OPEN, { xPos, yPos });
					break;
				case END_GOAL:
					GenerateSprite(TileNames::END_GOAL, { xPos, yPos });
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

			if (mAnimWorldSprites.at(yPos)->at(xPos) != nullptr)
			{
				delete mAnimWorldSprites.at(yPos)->at(xPos);
				mAnimWorldSprites.at(yPos)->at(xPos) = nullptr;
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

void CLevel::GenerateAnimatedWorldSprite(vector<const char*> spriteList, SVector2D<int> position)
{
	if (mWorldSprites[position.x]->at(position.y) != nullptr)
	{
		// Remove exsiting
		delete mWorldSprites[position.x]->at(position.y);
		mWorldSprites[position.x]->at(position.y) = nullptr;
	}
	mAnimWorldSprites[position.x]->at(position.y) = new CAnimatedWorldSprite(spriteList, { (float)position.x, (float)position.y, G_SPRITE_LAYER_Z_POS[ESpriteLayers::Floor] });
}