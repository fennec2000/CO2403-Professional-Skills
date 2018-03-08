// CLevel.cpp 02-03-2018
// William John Atkin WJAtkin@UCLan.ac.uk
#include "BUILD_ORDER.h"

CLevel::CLevel()
{
	// Sets the pointers
	mpEngine = CCore::GetInstance()->GetTLEngine();
	mpInput = CCore::GetInstance()->GetInput();

	// Creates the highlight sprite
	cursorHighlightSprite = new CWorldSprite(HIGHLIGHT_SPRITE_NAME, DEFAULT_SPRITE_POS);

	// Creates the tile map fully and fills it with NO_TILE
	// Also fills the sprite level tiles with empty sprites
	for (int i = 0; i < MAP_MAX_SIZE.x; i++)
	{
		tileMap.push_back(new vector<ETileType>);
		levelSprites.push_back(new vector<CWorldSprite*>);

		for (int j = 0; j < MAP_MAX_SIZE.y; j++)
		{
			tileMap[i]->push_back(NO_TILE);

			// Dont bother genrateing sprites for void tile as this tanks TL-Engines performace
			//levelSprites[i]->push_back(new CWorldSprite(VOID_TILE_SPRITE_NAME, {(float)i, (float)j, LEVEL_TILE_Z_POS}));
			//levelSprites[i]->at(j)->SetZ(-50.0f);

			// Insted we will init the pointer to NULL
			levelSprites[i]->push_back(nullptr);
		}
	}
}

CLevel::~CLevel()
{

}

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

	// Checks if the user wants to change tile type
	if (inputHandle->KeyHit(tle::Key_0))
		currentlySelectedTile = NO_TILE;
	if (inputHandle->KeyHit(tle::Key_1))
		currentlySelectedTile = WALL;
	if (inputHandle->KeyHit(tle::Key_2))
		currentlySelectedTile = FLOOR;
	if (inputHandle->KeyHit(tle::Key_3))
		currentlySelectedTile = SPAWN;
	if (inputHandle->KeyHit(tle::Key_4))
		currentlySelectedTile = WALL_WITH_SIDE;
	if (inputHandle->KeyHit(tle::Key_5))
		currentlySelectedTile = WALL_WITH_SIDE_FLIPPED_Y;

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
	if (isMouseInlevelWindow && isMouseOnTileMap && inputHandle->KeyHeld(tle::Mouse_LButton))
	{
		int xPos = static_cast<int>(tilePos.x);
		int yPos = static_cast<int>(tilePos.y);

		// Changes the tile map
		tileMap[xPos]->at(yPos) = currentlySelectedTile;

		// Checks if the user is deleting tiles
		if (currentlySelectedTile == NO_TILE)
		{
			// Delete the sprite
			delete levelSprites[xPos]->at(yPos);
			levelSprites[xPos]->at(yPos) = nullptr;
			return;
		}

		// Creates a sprite if it is null
		if (levelSprites[xPos]->at(yPos) == nullptr)
		{
			levelSprites[xPos]->at(yPos) = new CWorldSprite("", { (float)xPos, (float)yPos, LEVEL_TILE_Z_POS });
		}

		// Changes the sprite
		switch (currentlySelectedTile)
		{
		case WALL:
			levelSprites[xPos]->at(yPos)->SetSpriteSkin("FullWall.png");
			levelSprites[xPos]->at(yPos)->ResetZRot();
			break;
		case FLOOR:
			levelSprites[xPos]->at(yPos)->SetSpriteSkin("Floor.png");
			levelSprites[xPos]->at(yPos)->ResetZRot();
			break;
		case SPAWN:
			levelSprites[xPos]->at(yPos)->SetSpriteSkin("FloorSpawn.png");
			levelSprites[xPos]->at(yPos)->ResetZRot();
			break;
		case WALL_WITH_SIDE:
			levelSprites[xPos]->at(yPos)->SetSpriteSkin("WallSide.png");
			levelSprites[xPos]->at(yPos)->ResetZRot();
			break;
		case WALL_WITH_SIDE_FLIPPED_Y:
			levelSprites[xPos]->at(yPos)->SetSpriteSkin("WallSide.png");
			levelSprites[xPos]->at(yPos)->ResetZRot();
			levelSprites[xPos]->at(yPos)->RotateZ(180.0f);
			break;
		}
		
	}

}

void CLevel::ExportLevel()
{
	ofstream myOutputFile;
	myOutputFile.open("MapFile.txt");

	for (int i = 0; i < MAP_MAX_SIZE.x; i++)
	{
		for (int j = 0; j < MAP_MAX_SIZE.y; j++)
		{
			myOutputFile << tileMap[j]->at(i) << " ";
		}
		myOutputFile << "\n";
	}

	myOutputFile.close();
}

void CLevel::LoadLevel()
{
	std::ifstream mapFile;

	vector<vector<ETileType>*> newTileMap;

	// Open the file and check if it worked
	mapFile.open("MapFile.txt");
	if (!mapFile)
	{
		return;
	}
	std::cout << "Running!\n";
	// Creates the tile map fully and fills it with NO_TILE
	for (int i = 0; i < MAP_MAX_SIZE.x; i++)
	{
		newTileMap.push_back(new vector<ETileType>);
		for (int j = 0; j < MAP_MAX_SIZE.y; j++)
		{
			newTileMap[i]->push_back(NO_TILE);
		}
	}

	// Reads the file
	char ch;
	int xPos = 0;
	int yPos = 0;
	while (mapFile.get(ch))
	{
		// Checks if char is valid
		switch (ch)
		{
		case (char)NO_TILE + 48:
			delete levelSprites[xPos]->at(yPos);
			levelSprites[xPos]->at(yPos) = nullptr;
			break;

		case (char)WALL + 48:
			newTileMap[xPos]->at(yPos) = WALL;
			GenerateSprite("FullWall.png", {xPos, yPos});
			break;

		case (char)FLOOR + 48:
			newTileMap[xPos]->at(yPos) = FLOOR;
			GenerateSprite("Floor.png", { xPos, yPos });
			break;

		case (char)WALL_WITH_SIDE + 48:
			newTileMap[xPos]->at(yPos) = WALL_WITH_SIDE;
			GenerateSprite("WallSide.png", { xPos, yPos });
			break;

		case (char)WALL_WITH_SIDE_FLIPPED_Y + 48:
			newTileMap[xPos]->at(yPos) = WALL_WITH_SIDE_FLIPPED_Y;
			GenerateSprite("WallSide.png", { xPos, yPos });
			levelSprites[xPos]->at(yPos)->RotateZ(180.0f);
			break;

		case (char)SPAWN + 48:
			newTileMap[xPos]->at(yPos) = SPAWN;
			GenerateSprite("FloorSpawn.png", { xPos, yPos });
			break;

		case ' ':
			// Blank, do nothing
			break;

		case '\n':
			yPos++;
			xPos = 0;
			break;

		default:
			// Char is invalid
			mapFile.close();
			return;
		}

		if (ch != ' ' && ch != '\n')
		{
			xPos++;
		}
	}

	// Delete old tile map and use this new one
	for (int i = 0; i < MAP_MAX_SIZE.y; i++)
	{
		delete tileMap[i];
	}
	tileMap = newTileMap;

	// Close file
	mapFile.close();
}

void CLevel::ChangeSelectedTile(ETileType tileType)
{
	currentlySelectedTile = tileType;
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

void CLevel::GenerateSprite(const char* pSpriteName, SVector2D<int> position)
{
	if (levelSprites[position.x]->at(position.y) == nullptr)
	{
		// Generate the sprite
		levelSprites[position.x]->at(position.y) = new CWorldSprite(pSpriteName, { (float)position.x, (float)position.y, LEVEL_TILE_Z_POS });
	}
	else
	{
		// Change the existing skin
		levelSprites[position.x]->at(position.y)->SetSpriteSkin(pSpriteName);
		levelSprites[position.x]->at(position.y)->ResetZRot();
	}
}