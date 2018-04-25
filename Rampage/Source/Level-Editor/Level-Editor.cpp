// Level-Editor.cpp: A program using the TL-Engine
#include "BUILD_ORDER.h"
using namespace tle;

const char* TEMP_FILE_NAME = "..\\RampageGame\\tempMap";

#ifdef _DEBUG
	const char* GAME_EXE_FILE_PATH = "..\\RampageGame\\RampageGame.exe";
#else
	const char* GAME_EXE_FILE_PATH = "..\\RampageGame\\RampageGame.exe";
#endif // DEBUG

void main()
{
	// Creates the Core
	CCore* pCore = CCore::GetInstance();

	/**** Set up your scene here ****/

	// Sets up the UI BG
	CUISprite* topBarBGSprite = new CUISprite("TopBarBG.png", { 0.0f, 0.0f });
	CUISprite* tileBarBGSprite = new CUISprite("TileBarBG.png", { 960.0f, 72.0f });
	CUISprite* tileInfoBGSprite = new CUISprite("TileInfoBG.png", { 960.0f, 504.0f });

	// Sets up the save/load buttons
	// Save Button
	SUIData saveButtonData;
	saveButtonData.mPosition = { 12.0f, 12.0f };
	saveButtonData.mSize = { 70 , 45};
	saveButtonData.mSpriteXSize = 3;
	saveButtonData.mSpritePaths.push_back("ButtonLeft.png");
	saveButtonData.mSpritePaths.push_back("ButtonMiddle.png");
	saveButtonData.mSpritePaths.push_back("ButtonRight.png");
	saveButtonData.mHoverSpritePaths.push_back("ButtonLeft.png");
	saveButtonData.mHoverSpritePaths.push_back("ButtonMiddleHover.png");
	saveButtonData.mHoverSpritePaths.push_back("ButtonRight.png");
	// Creates the button
	CButton* saveButton = new CButton(&saveButtonData, "Save");

	// Load Button
	SUIData loadButtonData;
	loadButtonData.mPosition = { 94.0f, 12.0f };
	loadButtonData.mSize = { 70 , 45 };
	loadButtonData.mSpriteXSize = 3;
	loadButtonData.mSpritePaths.push_back("ButtonLeft.png");
	loadButtonData.mSpritePaths.push_back("ButtonMiddle.png");
	loadButtonData.mSpritePaths.push_back("ButtonRight.png");
	loadButtonData.mHoverSpritePaths.push_back("ButtonLeft.png");
	loadButtonData.mHoverSpritePaths.push_back("ButtonMiddleHover.png");
	loadButtonData.mHoverSpritePaths.push_back("ButtonRight.png");
	// Creates the button
	CButton* loadButton = new CButton(&loadButtonData, "Load");

	// File path text box
	SUIData textBoxData;
	textBoxData.mPosition = { 176.0f, 19.0f };
	textBoxData.mSize = { 250, 30 };
	textBoxData.mSpriteXSize = 2;
	textBoxData.mSpritePaths.push_back("TextBoxLeft.png");
	textBoxData.mSpritePaths.push_back("TextBoxMid.png");
	textBoxData.mSpritePaths.push_back("TextBoxRight.png");
	textBoxData.mHoverSpritePaths.push_back("TextBoxLeftHover.png");
	textBoxData.mHoverSpritePaths.push_back("TextBoxMidHover.png");
	textBoxData.mHoverSpritePaths.push_back("TextBoxRightHover.png");
	// Creates the text box
	CTextInputBox* filePathBox = new CTextInputBox(&textBoxData, "Cursor.png", "Enter file path...");

	// Title fonts for the 2 side tabs
	IFont* tileBarTitleFont = pCore->GetTLEngine()->LoadFont("Font1.bmp");
	IFont* tileInfoBarTitleFont = pCore->GetTLEngine()->LoadFont("Font1.bmp");

	// Delete button & font hint
	CButtonSprite* deleteButton = new CButtonSprite("BinIcon.png", "BinIconHover.png", { 975.0f, 425.0f }, { 64.0f, 64.0f });
	IFont* deleteTileFont = pCore->GetTLEngine()->LoadFont("Font1.bmp");

	// Selectable spawner buttons
	CButtonSprite* deleteSpawnButton = new CButtonSprite("BinSmall.png", "BinSmallHover.png", { 1200, 12.0f }, { 45, 45 });
	CButtonSprite* playerSpawnButton = new CButtonSprite("PlayerSpawn.png", "PlayerSpawnHover.png", { 1145, 12.0f }, { 45, 45 });
	CButtonSprite* chainEnemySpawnButton = new CButtonSprite("ChainEnemySpawn.png", "ChainEnemySpawnHover.png", { 1090, 12.0f }, { 45, 45 });
	CButtonSprite* shotEnemySpawnButton = new CButtonSprite("ShotEnemySpawn.png", "ShotEnemySpawnHover.png", { 1040, 12.0f }, { 45, 45 });
	CButtonSprite* randEnemySpawnButton = new CButtonSprite("RandEnemySpawn.png", "RandEnemySpawnHover.png", { 985, 12.0f }, { 45, 45 });

	// Selectable tile buttons
	CButtonSprite* FullWallButton = new CButtonSprite("FullWall.png", "FullWallHover.png", { 975.0f, 120.0f }, { 64.0f, 64.0f });
	CButtonSprite* FloorButton = new CButtonSprite("Floor.png", "FloorHover.png", { 1049.0f, 120.0f }, { 64.0f, 64.0f });
	CButtonSprite* WallSideButton = new CButtonSprite("WallSide.png", "WallSideHover.png", { 1123.0f, 120.0f }, { 64.0f, 64.0f });
	CButtonSprite* WallSideFlipedButton = new CButtonSprite("WallSideFliped.png", "WallSideFlipedHover.png", { 1197.0f, 120.0f }, { 64.0f, 64.0f });
	CButtonSprite* WallServerButton = new CButtonSprite("wallServer1.png", "wallServerHover.png", { 975.0f, 194.0f }, { 64.0f, 64.0f });
	CButtonSprite* DoorButton = new CButtonSprite("FloorDoor.png", "FloorDoorHover.png", { 1049.0f, 194.0f }, { 64.0f, 64.0f });
	CButtonSprite* DoorRotButton = new CButtonSprite("FloorDoorRot.png", "FloorDoorRotHover.png", { 1123.0f, 194.0f }, { 64.0f, 64.0f });
	CButtonSprite* EndGoalButton = new CButtonSprite("EndGoal.png", "EndGoalHover.png", { 1197.0f, 194.0f }, { 64.0f, 64.0f });

	// Room buttons
	CButtonSprite* roomButton = new CButtonSprite("Room.png", "RoomHover.png", { 600, 12.0f }, { 45, 45 });
	CButtonSprite* roomClearButton = new CButtonSprite("Clear.png", "ClearHover.png", { 657, 12.0f }, { 91, 45 });

	// The play button
	CButtonSprite* playButton = new CButtonSprite("Play.png", "PlayHover.png", { 438, 12.0f }, { 45, 45 });

	// The selected tile
	CButtonSprite* selectedTile = new CButtonSprite("Floor.png", "Floor.png", { 1000, 590}, { 45,45 });
	IFont* selectedFont = pCore->GetTLEngine()->LoadFont("Font1.bmp");

	// Force the floor to be selected by default
	pCore->GetLevel()->ChangeSelectedTile(FLOOR);

	// The main game loop, repeat until engine is stopped
	while (pCore->GetTLEngine()->IsRunning())
	{
		// Draw the scene
		pCore->UpdateCore();

		/**** Update your scene each frame here ****/

		// Update ui elements
		if (saveButton->Update())
		{
			pCore->GetLevel()->ExportLevel(filePathBox->GetInputedText().c_str());
		}
		if (loadButton->Update())
		{
			pCore->GetLevel()->LoadLevel(filePathBox->GetInputedText().c_str());
		}
		if (playButton->CheckClick())
		{
			// Create a tempory file
			pCore->GetLevel()->ExportLevel(TEMP_FILE_NAME);

			// Send the data off to the game and load it up
			std::string msg = GAME_EXE_FILE_PATH;
			msg += " ";
			msg += TEMP_FILE_NAME;
			system(msg.c_str());
		}
		filePathBox->Update();

		// Spawner buttons
		if (deleteSpawnButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSpawnerType(SPAWN_NOTHING);
			selectedTile->ChangeSprites("BinIcon.png", "BinIcon.png");
		}
		if (playerSpawnButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSpawnerType(SPAWN_PLAYER);
			selectedTile->ChangeSprites("PlayerSpawn.png", "PlayerSpawn.png");
		}
		if (chainEnemySpawnButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSpawnerType(SPAWN_CHAIN_ENEMY);
			selectedTile->ChangeSprites("ChainEnemySpawn.png", "ChainEnemySpawn.png");
		}
		if (shotEnemySpawnButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSpawnerType(SPAWN_SHOT_ENEMY);
			selectedTile->ChangeSprites("ShotEnemySpawn.png", "ShotEnemySpawn.png");
		}
		if (randEnemySpawnButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSpawnerType(SPAWN_RAND_ENEMY);
			selectedTile->ChangeSprites("RandEnemySpawn.png", "RandEnemySpawn.png");
		}

		// Tiles
		if (deleteButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSelectedTile(NO_TILE);
			selectedTile->ChangeSprites("BinIcon.png", "BinIcon.png");
		}
		if (FullWallButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSelectedTile(WALL);
			selectedTile->ChangeSprites("FullWall.png", "FullWall.png");
		}
		if (FloorButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSelectedTile(FLOOR);
			selectedTile->ChangeSprites("Floor.png", "Floor.png");
		}
		if (WallSideButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSelectedTile(WALL_WITH_SIDE);
			selectedTile->ChangeSprites("WallSide.png", "WallSide.png");
		}
		if (WallSideFlipedButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSelectedTile(WALL_WITH_SIDE_FLIPPED_Y);
			selectedTile->ChangeSprites("WallSideFliped.png", "WallSideFliped.png");
		}
		if (WallServerButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSelectedTile(WALL_SERVER_ANIMATED);
			selectedTile->ChangeSprites("wallServer1.png", "wallServer1.png");
		}
		if (DoorButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSelectedTile(DOOR);
			selectedTile->ChangeSprites("FloorDoor.png", "FloorDoor.png");
		}
		if (DoorRotButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSelectedTile(DOOR_ROT);
			selectedTile->ChangeSprites("FloorDoorRot.png", "FloorDoorRot.png");
		}
		if (EndGoalButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSelectedTile(END_GOAL);
			selectedTile->ChangeSprites("EndGoal.png", "EndGoal.png");
		}

		if (roomButton->CheckClick())
		{
			pCore->GetLevel()->SelectRoomTool();
			selectedTile->ChangeSprites("Room.png", "Room.png");
		}
		if (roomClearButton->CheckClick())
		{
			pCore->GetLevel()->ClearRooms();
		}

		// Fonts
		tileBarTitleFont->Draw("Tiles", 1090, 80);
		tileInfoBarTitleFont->Draw("Selected Tool/Tile", 1040, 520);
		deleteTileFont->Draw("Remove Tile", 1070, 450);

		// Selection font
		EToolMode toolMode = pCore->GetLevel()->GetToolMode();
		if (toolMode == TILES)
		{
			ETileType currentTile = pCore->GetLevel()->GetCurrentTile();
			switch (currentTile)
			{
			case NO_TILE:
				selectedFont->Draw("Delete Tile", 1074, 610);
				break;
			case WALL:
				selectedFont->Draw("Wall Tile", 1074, 610);
				break;
			case FLOOR:
				selectedFont->Draw("Floor Tile", 1074, 610);
				break;
			case WALL_WITH_SIDE:
				selectedFont->Draw("Wall Tile", 1074, 610);
				break;
			case WALL_WITH_SIDE_FLIPPED_Y:
				selectedFont->Draw("Wall Tile", 1074, 610);
				break;
			case WALL_SERVER_ANIMATED:
				selectedFont->Draw("Server Tile", 1074, 610);
				break;
			case DOOR:
				selectedFont->Draw("Door Tile", 1074, 610);
				break;
			case DOOR_ROT:
				selectedFont->Draw("Door Tile", 1074, 610);
				break;
			case END_GOAL:
				selectedFont->Draw("Goal Tile", 1074, 610);
				break;
			}
		}
		else if (toolMode == SPAWNERS)
		{
			ESpawnTypes currentSpawner = pCore->GetLevel()->GetCurrentSpawner();
			switch (currentSpawner)
			{
			case SPAWN_NOTHING:
				selectedFont->Draw("Delete Spawner", 1074, 610);
				break;
			case SPAWN_PLAYER:
				selectedFont->Draw("Spawn Player", 1074, 610);
				break;
			case SPAWN_CHAIN_ENEMY:
				selectedFont->Draw("Chaingun Enemy", 1074, 610);
				break;
			case SPAWN_SHOT_ENEMY:
				selectedFont->Draw("Shotgun Enemy", 1074, 610);
				break;
			case SPAWN_RAND_ENEMY:
				selectedFont->Draw("Random Enemy", 1074, 610);
				break;
			}
		}
		else
		{
			selectedFont->Draw("Create Room", 1074, 610);
		}

		// Checks if the user wishes to exit
		if (pCore->GetInput()->KeyHit(Key_Escape))
			pCore->GetTLEngine()->Stop();
	}
}
