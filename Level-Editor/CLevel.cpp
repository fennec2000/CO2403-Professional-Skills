// CLevel.cpp 02-03-2018
// William John Atkin WJAtkin@UCLan.ac.uk
#include "BUILD_ORDER.h"

const SVector2D<int> CLevel::MAP_MAX_SIZE = { 128, 128 };

CLevel::CLevel()
{
	// Sets the pointers
	mpEngine = CCore::GetInstance()->GetTLEngine();

	// Creates the highlight sprite
	cursorHighlightSprite = new CWorldSprite(HIGHLIGHT_SPRITE_NAME, DEFAULT_SPRITE_POS, BLEND_MULTIPLICATIVE);

	// Fills the sprite level tiles with empty sprites
	for (int i = 0; i < MAP_MAX_SIZE.x; i++)
	{
		mMapSprites.push_back(new vector<CWorldSprite*>);
		mSpawnerSprites.push_back(new vector<CWorldSprite*>);
		for (int j = 0; j < MAP_MAX_SIZE.y; j++)
		{
			// Dont bother genrateing sprites for void tile as this tanks TL-Engine performace
			//levelSprites[i]->push_back(new CWorldSprite(VOID_TILE_SPRITE_NAME, {(float)i, (float)j, LEVEL_TILE_Z_POS}));
			//levelSprites[i]->at(j)->SetZ(-50.0f);

			// Insted we will init the pointer to NULL
			mMapSprites[i]->push_back(nullptr);
			mSpawnerSprites[i]->push_back(nullptr);
		}
	}
}

CLevel::~CLevel() { }

void CLevel::Update()
{
	// Pans the camera
	tle::ICamera* camera = CCore::GetInstance()->GetCamera();
	CInput* inputHandle = CCore::GetInstance()->GetInput();
	float* deltaTime = CCore::GetInstance()->GetFrameTimer();
	if (inputHandle->KeyHeld(PAN_UP))
	{
		camera->MoveLocalY((*deltaTime) * CAMERA_PAN_SPEED);
	}
	else if (inputHandle->KeyHeld(PAN_Down))
	{
		camera->MoveLocalY(-(*deltaTime) * CAMERA_PAN_SPEED);
	}
	if (inputHandle->KeyHeld(PAN_RIGHT))
	{
		camera->MoveLocalX((*deltaTime) * CAMERA_PAN_SPEED);
	}
	else if (inputHandle->KeyHeld(PAN_LEFT))
	{
		camera->MoveLocalX(-(*deltaTime) * CAMERA_PAN_SPEED);
	}

	// Checks if the mouse is in the level window
	SVector2D<float> mousePos = { static_cast<float>(mpEngine->GetMouseX()), static_cast<float>(mpEngine->GetMouseY()) };
	bool isMouseInlevelWindow = false;
	if (mousePos.x >= minPos.x && mousePos.x <= maxPos.x)
	{
		if (mousePos.y >= minPos.y && mousePos.y <= maxPos.y)
		{
			isMouseInlevelWindow = true;
		}
	}

	// Checks if the mouse is over a valid position on the tile map
	SVector2D<float> tilePos = findCursorTilePos();
	bool isMouseOnTileMap = false;
	if (tilePos.x >= 0.0f && static_cast<int>(tilePos.x) < MAP_MAX_SIZE.x)
	{
		if (tilePos.y >= 0.0f && static_cast<int>(tilePos.y) < MAP_MAX_SIZE.y)
		{
			isMouseOnTileMap = true;
		}
	}

	// Updates the cursor highlight tile base on parameters
	if (isMouseInlevelWindow)
	{
		// Update the position of the tile
		cursorHighlightSprite->SetPosition({ tilePos.x, tilePos.y });
		cursorHighlightSprite->SetZ(DEFAULT_SPRITE_POS.z);

		if (isMouseOnTileMap)
		{
			// Set the tile to blue
			cursorHighlightSprite->SetSpriteSkin(HIGHLIGHT_SPRITE_NAME);
		}
		else
		{
			// Show that the tile is out of bounds and change
			// highlight color to red
			cursorHighlightSprite->SetSpriteSkin(HIGHLIGHT_OUT_OF_BOUNDS_SPRITE_NAME);
		}								
	}
	else
	{
		// Hide the tile
		cursorHighlightSprite->SetZ(HIDE_Z_POS);
	}

	// Checks if the user has clicked over a valid tile
	if (isMouseInlevelWindow && isMouseOnTileMap && inputHandle->KeyHeld(tle::Mouse_LButton) && mSelectedMode != 3)
	{
		int xPos = static_cast<int>(tilePos.x);
		int yPos = static_cast<int>(tilePos.y);

		// Checks the mode
		if (mSelectedMode == 1)
		{
			// Changes the tile map
			mMapData.mTileMap[yPos].at(xPos) = currentlySelectedTile;

			// Checks if the user is deleting tiles
			if (currentlySelectedTile == NO_TILE)
			{
				// Delete the sprite
				delete mMapSprites[xPos]->at(yPos);
				mMapSprites[xPos]->at(yPos) = nullptr;
				return;
			}

			// Creates a sprite if it is null
			if (mMapSprites[xPos]->at(yPos) == nullptr)
			{
				mMapSprites[xPos]->at(yPos) = new CWorldSprite("", { (float)xPos, (float)yPos, LEVEL_TILE_Z_POS });
			}

			// Changes the sprite
			switch (currentlySelectedTile)
			{
			case WALL:
				mMapSprites[xPos]->at(yPos)->SetSpriteSkin(TileNames::FULL_WALL);
				break;
			case FLOOR:
				mMapSprites[xPos]->at(yPos)->SetSpriteSkin(TileNames::FLOOR);
				break;
			case WALL_WITH_SIDE:
				mMapSprites[xPos]->at(yPos)->SetSpriteSkin(TileNames::WALL_SIDE);
				break;
			case WALL_WITH_SIDE_FLIPPED_Y:
				mMapSprites[xPos]->at(yPos)->SetSpriteSkin(TileNames::WALL_SIDE_FLIPPED_Y);
				break;
			case WALL_SERVER_ANIMATED:
				mMapSprites[xPos]->at(yPos)->SetSpriteSkin(TileNames::WALL_SERVER_ANIMATED);
				break;
			case DOOR:
				mMapSprites[xPos]->at(yPos)->SetSpriteSkin(TileNames::DOOR);
				break;
			case DOOR_ROT:
				mMapSprites[xPos]->at(yPos)->SetSpriteSkin(TileNames::DOOR_ROT);
				break;
			}
		}
		else if (mSelectedMode == 2)
		{
			// Changes the spawner
			mMapData.mSpawnerMap[yPos].at(xPos) = currentlySelectedSpawner;

			// Checks if the user is deleting spawners
			if (currentlySelectedSpawner == SPAWN_NOTHING)
			{
				// Delete the sprite
				delete mSpawnerSprites[xPos]->at(yPos);
				mSpawnerSprites[xPos]->at(yPos) = nullptr;
				return;
			}

			// Creates a sprite if it is null
			if (mSpawnerSprites[xPos]->at(yPos) == nullptr)
			{
				mSpawnerSprites[xPos]->at(yPos) = new CWorldSprite("", { (float)xPos, (float)yPos, LEVEL_TILE_Z_POS - 0.1f }, BLEND_CUTOUT);
			}

			// Changes the sprite
			switch (currentlySelectedSpawner)
			{
			case SPAWN_PLAYER:
				mSpawnerSprites[xPos]->at(yPos)->SetSpriteSkin(SpawnerNames::PLAYER_SPAWN);
				break;
			case SPAWN_ENEMY:
				mSpawnerSprites[xPos]->at(yPos)->SetSpriteSkin(SpawnerNames::ENEMY_SPAWN);
				break;
			case SPAWN_CHAIN_ENEMY:
				mSpawnerSprites[xPos]->at(yPos)->SetSpriteSkin(SpawnerNames::ENEMY_CHAIN_SPAWN);
				break;
			case SPAWN_SHOT_ENEMY:
				mSpawnerSprites[xPos]->at(yPos)->SetSpriteSkin(SpawnerNames::ENEMY_SHOT_SPAWN);
				break;
			case SPAWN_RAND_ENEMY:
				mSpawnerSprites[xPos]->at(yPos)->SetSpriteSkin(SpawnerNames::ENEMY_RAND_SPAWN);
				break;
			}
		}
	}
	else if (isMouseInlevelWindow && isMouseOnTileMap && mSelectedMode == 3)
	{
		int xPos = static_cast<int>(tilePos.x);
		int yPos = static_cast<int>(tilePos.y);

		if (currentlyHighlightingRoom)
		{
			// Check if the user realsed the mouse this frame
			if (!inputHandle->KeyHeld(Mouse_LButton))
			{
				// record the room and generate sprites
				SRoomData newRoom;
				newRoom.mMinPos = roomStartPos;
				newRoom.mMaxPos = { xPos, yPos };
				mMapData.mRoomData.push_back(newRoom);

				// Remove the sprites
				while (roomHighLightSprites.size() > 0)
				{
					delete roomHighLightSprites[0];
					roomHighLightSprites.erase(roomHighLightSprites.begin());
				}

				// Create new ones, for the x first
				for (int i = roomStartPos.x; i < xPos; i++)
				{
					roomSprites.push_back(new CWorldSprite(ROOM_WALL_SPRITE, { static_cast<float>(i), static_cast<float>(roomStartPos.y), DEFAULT_SPRITE_POS.z }, BLEND_CUTOUT));
					roomSprites.push_back(new CWorldSprite(ROOM_WALL_SPRITE, { static_cast<float>(i), static_cast<float>(yPos), DEFAULT_SPRITE_POS.z }, BLEND_CUTOUT));
				}
				// Then for the y
				for (int i = roomStartPos.y; i <= yPos; i++)
				{
					roomSprites.push_back(new CWorldSprite(ROOM_WALL_SPRITE, { static_cast<float>(roomStartPos.x), static_cast<float>(i), DEFAULT_SPRITE_POS.z }, BLEND_CUTOUT));
					roomSprites.push_back(new CWorldSprite(ROOM_WALL_SPRITE, { static_cast<float>(xPos), static_cast<float>(i), DEFAULT_SPRITE_POS.z }, BLEND_CUTOUT));
				}

				currentlyHighlightingRoom = false;
			}
			else
			{
				// Update the highlight sprites
				// Firstly by destorying the current ones
				while (roomHighLightSprites.size() > 0)
				{
					delete roomHighLightSprites[0];
					roomHighLightSprites.erase(roomHighLightSprites.begin());
				}

				// Create new ones, for the x first
				for (int i = roomStartPos.x; i < xPos; i++)
				{
					roomHighLightSprites.push_back(new CWorldSprite(ROOM_HIGHLIGHT_SPRITE, {static_cast<float>(i), static_cast<float>(roomStartPos.y), DEFAULT_SPRITE_POS.z }, BLEND_MULTIPLICATIVE));
					roomHighLightSprites.push_back(new CWorldSprite(ROOM_HIGHLIGHT_SPRITE, { static_cast<float>(i), static_cast<float>(yPos), DEFAULT_SPRITE_POS.z }, BLEND_MULTIPLICATIVE));
				}
				// Then for the y
				for (int i = roomStartPos.y; i <= yPos; i++)
				{
					roomHighLightSprites.push_back(new CWorldSprite(ROOM_HIGHLIGHT_SPRITE, { static_cast<float>(roomStartPos.x), static_cast<float>(i), DEFAULT_SPRITE_POS.z }, BLEND_MULTIPLICATIVE));
					roomHighLightSprites.push_back(new CWorldSprite(ROOM_HIGHLIGHT_SPRITE, { static_cast<float>(xPos), static_cast<float>(i), DEFAULT_SPRITE_POS.z }, BLEND_MULTIPLICATIVE));
				}
			}
		}
		else
		{
			if (inputHandle->KeyHeld(tle::Mouse_LButton))
			{
				roomStartPos = { xPos, yPos };
				currentlyHighlightingRoom = true;
			}
		}
	}
}

void CLevel::ExportLevel(const char* filePath)
{
	CMapIO::SaveMapFile(&mMapData, filePath);
}

void CLevel::LoadLevel(const char* filePath)
{
	UnloadMap();
	mMapData = CMapIO::ReadMapFile(filePath);
	GenerateMap();
}

void CLevel::GenerateMap()
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
					GenerateSprite(TileNames::WALL_SERVER_ANIMATED, { xPos, yPos });
				}
			}

			// Check if there is a spawner to display
			if (mMapData.mSpawnerMap[yPos].at(xPos) != SPAWN_NOTHING)
			{
				// Create the sprite
				switch (mMapData.mSpawnerMap[yPos].at(xPos))
				{
				case SPAWN_PLAYER:
					GenerateSprite(SpawnerNames::PLAYER_SPAWN, { xPos, yPos }, 2);
					break;
				case SPAWN_ENEMY:
					GenerateSprite(SpawnerNames::ENEMY_SPAWN, { xPos, yPos }, 2);
					break;
				case SPAWN_CHAIN_ENEMY:
					GenerateSprite(SpawnerNames::ENEMY_CHAIN_SPAWN, { xPos, yPos }, 2);
					break;
				case SPAWN_SHOT_ENEMY:
					GenerateSprite(SpawnerNames::ENEMY_SHOT_SPAWN, { xPos, yPos }, 2);
					break;
				case SPAWN_RAND_ENEMY:
					GenerateSprite(SpawnerNames::ENEMY_RAND_SPAWN, { xPos, yPos }, 2);
					break;
				}
			}
		}
	}
}

void CLevel::UnloadMap()
{
	// Reset all the data
	mMapData = SMapData();

	// Reset all of the sprites to NULL
	for (int i = 0; i < MAP_MAX_SIZE.x; i++)
	{
		for (int j = 0; j < MAP_MAX_SIZE.y; j++)
		{
			// Check if there is a sprite here
			if (mMapSprites[j]->at(i) != nullptr)
			{
				delete mMapSprites[j]->at(i);
				mMapSprites[j]->at(i) = nullptr;
			}
		}
	}
}

void CLevel::ChangeSelectedTile(ETileType tileType)
{
	currentlySelectedTile = tileType;
	mSelectedMode = 1;
}

void CLevel::ChangeSpawnerType(ESpawnTypes spawnType)
{
	currentlySelectedSpawner = spawnType;
	mSelectedMode = 2;
}

void CLevel::SelectRoomTool()
{
	mSelectedMode = 3;
}

void CLevel::ClearRooms()
{
	// Clear room data
	for (int i = 0; i < mMapData.mRoomData.size(); i++)
	{
		mMapData.mRoomData.erase(mMapData.mRoomData.begin());
	}

	// Remove the sprites
	// Highlighting
	while (roomHighLightSprites.size() > 0)
	{
		delete roomHighLightSprites[0];
		roomHighLightSprites.erase(roomHighLightSprites.begin());
	}
	// Rooms
	while (roomSprites.size() > 0)
	{
		delete  roomSprites[0];
		roomSprites.erase(roomSprites.begin());
	}
}

SVector2D<float> CLevel::findCursorTilePos()
{
	// Finds the mouse pixel position
	SVector2D<float> mousePos = { static_cast<float>(mpEngine->GetMouseX()), static_cast<float>(mpEngine->GetMouseY()) };
	// Gets where the center of the screen is
	tle::ICamera* camera = CCore::GetInstance()->GetCamera();
	SVector2D<float> screenPos = { camera->GetX(), camera->GetY() };
	SVector2D<int> windowSize = CCore::GetInstance()->GetWindowSize();
	SVector2D<float> worldSpace;

	// Finds the position in world space
	worldSpace.x = screenPos.x + (mousePos.x - static_cast<float>(windowSize.x / 2.0f)) / PIXELS_PER_METER;
	worldSpace.y = screenPos.y - (mousePos.y - static_cast<float>(windowSize.y / 2.0f)) / PIXELS_PER_METER;

	worldSpace.x += 0.5f;
	worldSpace.y += 0.5f;

	// Convert it to the grid
	worldSpace.x = floorf(worldSpace.x);
	worldSpace.y = floorf(worldSpace.y);

	return worldSpace;
}

void CLevel::GenerateSprite(const char* pSpriteName, SVector2D<int> position, int selectedMode)
{
	if (selectedMode == 1)
	{
		if (mMapSprites[position.x]->at(position.y) == nullptr)
		{
			// Generate the sprite
			mMapSprites[position.x]->at(position.y) = new CWorldSprite(pSpriteName, { (float)position.x, (float)position.y, LEVEL_TILE_Z_POS });
		}
		else
		{
			// Change the existing skin
			mMapSprites[position.x]->at(position.y)->SetSpriteSkin(pSpriteName);
			mMapSprites[position.x]->at(position.y)->ResetZRot();
		}
	}
	else if (selectedMode == 2)
	{
		if (mSpawnerSprites[position.x]->at(position.y) == nullptr)
		{
			// Generate the sprite
			mSpawnerSprites[position.x]->at(position.y) = new CWorldSprite(pSpriteName, { (float)position.x, (float)position.y, LEVEL_TILE_Z_POS - 0.1f }, BLEND_CUTOUT);
		}
		else
		{
			// Change the existing skin
			mSpawnerSprites[position.x]->at(position.y)->SetSpriteSkin(pSpriteName);
			mSpawnerSprites[position.x]->at(position.y)->ResetZRot();
		}
	}
}