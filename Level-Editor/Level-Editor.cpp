// Level-Editor.cpp: A program using the TL-Engine
#include "BUILD_ORDER.h"
using namespace tle;

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

	// Title fonts for the 2 side tabs
	IFont* tileBarTitleFont = pCore->GetTLEngine()->LoadFont("Font1.bmp");
	IFont* tileInfoBarTitleFont = pCore->GetTLEngine()->LoadFont("Font1.bmp");

	// Delete button & font hint
	CButtonSprite* deleteButton = new CButtonSprite("BinIcon.png", "BinIconHover.png", { 975.0f, 425.0f }, { 64.0f, 64.0f });
	IFont* deleteTileFont = pCore->GetTLEngine()->LoadFont("Font1.bmp");

	// Selectable tile buttons
	CButtonSprite* FullWallButton = new CButtonSprite("FullWall.png", "FullWall.png", { 975.0f, 120.0f }, { 64.0f, 64.0f });
	CButtonSprite* FloorButton = new CButtonSprite("Floor.png", "Floor.png", { 1049.0f, 120.0f }, { 64.0f, 64.0f });
	CButtonSprite* FloorSpawnButton = new CButtonSprite("FloorSpawn.png", "FloorSpawn.png", { 1123.0f, 120.0f }, { 64.0f, 64.0f });
	CButtonSprite* WallSideButton = new CButtonSprite("WallSide.png", "WallSide.png", { 1197.0f, 120.0f }, { 64.0f, 64.0f });

	// The main game loop, repeat until engine is stopped
	while (pCore->GetTLEngine()->IsRunning())
	{
		// Draw the scene
		pCore->UpdateCore();

		/**** Update your scene each frame here ****/

		// Update ui elements
		if (saveButton->Update())
		{
			pCore->GetLevel()->ExportLevel();
		}
		if (loadButton->Update())
		{
			pCore->GetLevel()->LoadLevel();
		}
		if (deleteButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSelectedTile(NO_TILE);
		}
		// Tiles
		if (FullWallButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSelectedTile(WALL);
		}
		if (FloorButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSelectedTile(FLOOR);
		}
		if (FloorSpawnButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSelectedTile(SPAWN);
		}
		if (WallSideButton->CheckClick())
		{
			pCore->GetLevel()->ChangeSelectedTile(WALL_WITH_SIDE);
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
