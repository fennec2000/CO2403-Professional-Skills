// Level-Editor.cpp: A program using the TL-Engine
#include "BUILD_ORDER.h"
using namespace tle;

const char* TEMP_FILE_NAME = "..\\tempMap";

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
	CButtonSprite* deleteSpawnButton = new CButtonSprite("BinSmall.png", "BinSmall.png", { 1200, 12.0f }, { 45, 45 });
	CButtonSprite* playerSpawnButton = new CButtonSprite("PlayerSpawn.png", "PlayerSpawn.png", { 1145, 12.0f }, { 45, 45 });
	CButtonSprite* enemySpawnButton = new CButtonSprite("EnemySpawn.png", "EnemySpawn.png", { 1090, 12.0f }, { 45, 45 });
	CButtonSprite* chainEnemySpawnButton = new CButtonSprite("ChainEnemySpawn.png", "ChainEnemySpawn.png", { 1040, 12.0f }, { 45, 45 });
	CButtonSprite* shotEnemySpawnButton = new CButtonSprite("ShotEnemySpawn.png", "ShotEnemySpawn.png", { 985, 12.0f }, { 45, 45 });
	CButtonSprite* randEnemySpawnButton = new CButtonSprite("RandEnemySpawn.png", "RandEnemySpawn.png", { 930, 12.0f }, { 45, 45 });

	// Selectable tile buttons
	CButtonSprite* FullWallButton = new CButtonSprite("FullWall.png", "FullWall.png", { 975.0f, 120.0f }, { 64.0f, 64.0f });
	CButtonSprite* FloorButton = new CButtonSprite("Floor.png", "Floor.png", { 1049.0f, 120.0f }, { 64.0f, 64.0f });
	CButtonSprite* WallSideButton = new CButtonSprite("WallSide.png", "WallSide.png", { 1123.0f, 120.0f }, { 64.0f, 64.0f });
	CButtonSprite* WallSideFlipedButton = new CButtonSprite("WallSideFliped.png", "WallSideFliped.png", { 1197.0f, 120.0f }, { 64.0f, 64.0f });
	CButtonSprite* WallServerButton = new CButtonSprite("wallServer1.png", "wallServer1.png", { 975.0f, 194.0f }, { 64.0f, 64.0f });
	CButtonSprite* DoorButton = new CButtonSprite("FloorDoor.png", "FloorDoor.png", { 1049.0f, 194.0f }, { 64.0f, 64.0f });
	CButtonSprite* DoorRotButton = new CButtonSprite("FloorDoorRot.png", "FloorDoorRot.png", { 1123.0f, 194.0f }, { 64.0f, 64.0f });
	CButtonSprite* EndGoalButton = new CButtonSprite("EndGoal.png", "EndGoal.png", { 1197.0f, 194.0f }, { 64.0f, 64.0f });

	// Room buttons
	CButtonSprite* roomButton = new CButtonSprite("Room.png", "Room.png", { 600, 12.0f }, { 45, 45 });
	CButtonSprite* roomClearButton = new CButtonSprite("Clear.png", "Clear.png", { 657, 12.0f }, { 91, 45 });

	// The play button
	CButtonSprite* playButton = new CButtonSprite("Play.png", "Play.png", { 438, 12.0f }, { 45, 45 });

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
			std::string msg = "..\\CO2403-Professional-Skills\\CO2403-Professional-SkillsDebug.exe";
			msg += " ";
			msg += TEMP_FILE_NAME;
			system(msg.c_str());
		}
		filePathBox->Update();

		// Spawner buttons
		if (deleteSpawnButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSpawnerType(SPAWN_NOTHING);
		}
		if (playerSpawnButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSpawnerType(SPAWN_PLAYER);
		}
		if (enemySpawnButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSpawnerType(SPAWN_ENEMY);
		}
		if (chainEnemySpawnButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSpawnerType(SPAWN_CHAIN_ENEMY);
		}
		if (shotEnemySpawnButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSpawnerType(SPAWN_SHOT_ENEMY);
		}
		if (randEnemySpawnButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSpawnerType(SPAWN_RAND_ENEMY);
		}

		// Tiles
		if (deleteButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSelectedTile(NO_TILE);
		}
		if (FullWallButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSelectedTile(WALL);
		}
		if (FloorButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSelectedTile(FLOOR);
		}
		if (WallSideButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSelectedTile(WALL_WITH_SIDE);
		}
		if (WallSideFlipedButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSelectedTile(WALL_WITH_SIDE_FLIPPED_Y);
		}
		if (WallServerButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSelectedTile(WALL_SERVER_ANIMATED);
		}
		if (DoorButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSelectedTile(DOOR);
		}
		if (DoorRotButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSelectedTile(DOOR_ROT);
		}
		if (EndGoalButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSelectedTile(END_GOAL);
		}

		if (roomButton->CheckClick())
		{
			pCore->GetLevel()->SelectRoomTool();
		}
		if (roomClearButton->CheckClick())
		{
			pCore->GetLevel()->ClearRooms();
		}

		// Fonts
		tileBarTitleFont->Draw("Tiles", 1090, 80);
		tileInfoBarTitleFont->Draw("Selected Tile", 1060, 510);
		deleteTileFont->Draw("Remove Tile", 1070, 450);

		// Checks if the user wishes to exit
		if (pCore->GetInput()->KeyHit(Key_Escape))
			pCore->GetTLEngine()->Stop();
	}
}
