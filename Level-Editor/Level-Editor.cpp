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

	// The main game loop, repeat until engine is stopped
	while (pCore->GetTLEngine()->IsRunning())
	{
		// Draw the scene
		pCore->UpdateCore();

		/**** Update your scene each frame here ****/

		// Update ui elements
		saveButton->Update();
		loadButton->Update();

		// Checks if the user wishes to exit
		if (pCore->GetInput()->KeyHit(Key_Escape))
			pCore->GetTLEngine()->Stop();
	}
}
