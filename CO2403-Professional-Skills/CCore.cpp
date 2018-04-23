#include "BUILD_ORDER.h"

// Setup instance
CCore* CCore::pInstance = 0;

CCore* CCore::GetInstance()
{
	if (pInstance == 0)
	{
		pInstance = new CCore();
	}

	return pInstance;
}

CCore::CCore()
{
	pInstance = this;

	// random
	srand(time(NULL));

	// Load engine
	pTLEngine = New3DEngine(kTLX);

	// Engine settings
	pTLEngine->StartWindowed();
	//pTLEngine->StartFullscreen();
	pTLEngine->AddMediaFolder("TestMedia");
	pTLEngine->AddMediaFolder("Media");
	pTLEngine->AddMediaFolder("Media\\Animation");

	// Input
	pInput = new CInput(pTLEngine);

	// Font
	for(int i = 0; i < EFontTypes::NumOfFontTypes; i++)
		pText[i] = pTLEngine->LoadFont("Lucida Sans", mTEXT_SIZE[i]);

	// Camera
	pCamera = pTLEngine->CreateCamera(kManual, 0.0f, 0.0f, -10.0f);

	// GUI
	pGUI = new CGUI(pTLEngine->GetHeight(), pTLEngine->GetWidth());

	// Data setup
	for (int i = 0; i < EPlayers::NumOfEPlayers; ++i)
		pPlayer[i] = nullptr;

	// set game state
	mGameState = EGameState::MainMenu;
	mGameScore = 0;

	// Creates the level
	pLevel = new CLevel();

	// Loads the main menu
	UnloadGame();
	SetupMenu();

	// for debuging
	pGUI->SetWeaponIcon(EWeapons::Shotgun);
}

CCore::~CCore()
{
	if (pPlayer[EPlayers::PlayerTeam] != NULL)
	{
		delete pPlayer[EPlayers::PlayerTeam];
		pPlayer[EPlayers::PlayerTeam] = NULL;
	}

	delete pGUI;
	delete pInput;
	delete pLevel;

	// Delete the 3D engine now we are finished with it
	pTLEngine->Delete();
}

void CCore::UpdateCore()
{
	// Draw the scene
	mFrameTime = pTLEngine->Timer();	// update the frame timer
	pTLEngine->DrawScene();				// draw the frame

	switch (mGameState)
	{
	case MainMenu:
		// temp
		pGUI->UpdateHealth(0);
		pGUI->SetWeaponHidden(true);
		if (pPlayButton->Update())
		{
			UnloadMenu();
			LoadLevel();
		}
		break;
	case Playing:
		// level update
		pLevel->Update();

		// player update
		pPlayer[EPlayers::PlayerTeam]->Update();

		//update each bullet
		for (int i = 0; i < pActiveBullets.size(); ++i)
		{
			if (pActiveBullets[i]->returnTeam() == EnemyTeam)
			{
				SVector2D<float> bulletPos = pActiveBullets[i]->GetPos2D();
				SVector2D<float> playerPos = GetPlayer(PlayerTeam)->GetPos2D();
				float distance = sqrt(((playerPos.x - bulletPos.x) * (playerPos.x - bulletPos.x)) + ((playerPos.y - bulletPos.y) * (playerPos.y - bulletPos.y)));
				if (distance < pActiveBullets[i]->getSize())
				{
					pActiveBullets[i]->Remove();
				}
			}
			else if (pActiveBullets[i]->returnTeam() == PlayerTeam)
			{
				vector<CEnemy*> enemies = pLevel->getEnemies();
				for (int k = 0; k < enemies.size(); k++)
				{
					SVector2D<float> enemyPos = enemies[k]->GetPos2D();
					SVector2D<float> bulletPos = pActiveBullets[i]->GetPos2D();
					float distance = sqrt(((enemyPos.x - bulletPos.x) * (enemyPos.x - bulletPos.x)) + ((enemyPos.y - bulletPos.y) * (enemyPos.y - bulletPos.y)));
					if (distance < pActiveBullets[i]->getSize())
					{
					    cout << "ow";
						enemies[k]->Hit();
						pActiveBullets[i]->Remove();
						cout << "blep";
					}
				}
			}

			pActiveBullets[i]->Update();
		}

		// exit key
		if (pInput->KeyHit(Key_Escape))
		{
			FlashLoadScreen();
			UnloadGame();
			pTLEngine->Stop();
		}

		break;
	case Paused:
		break;
	case GameOver:
		// show score
		pText[EFontTypes::Large]->Draw("Game over", pTLEngine->GetWidth() / 2, pTLEngine->GetHeight() / 2 - mTEXT_SPACING[EFontTypes::Large] * 3 / 2, tle::kRed, tle::kCentre, tle::kVCentre);
		pText[EFontTypes::Large]->Draw("Score:", pTLEngine->GetWidth() / 2, pTLEngine->GetHeight() / 2 - mTEXT_SPACING[EFontTypes::Large] / 2, tle::kRed, tle::kCentre, tle::kVCentre);
		pText[EFontTypes::Large]->Draw(to_string(mGameScore), pTLEngine->GetWidth() / 2, pTLEngine->GetHeight() / 2 + mTEXT_SPACING[EFontTypes::Large] / 2, tle::kRed, tle::kCentre, tle::kVCentre);
		pText[EFontTypes::Medium]->Draw("Press any key to return to the main menu", pTLEngine->GetWidth() / 2, pTLEngine->GetHeight() / 2 + mTEXT_SPACING[EFontTypes::Large] * 3 / 2 - mTEXT_SPACING[EFontTypes::Medium], tle::kRed, tle::kCentre, tle::kVCentre);

		// return key
		if (pTLEngine->AnyKeyHit())
		{
			UnloadGame();
			SetupMenu();
		}
		break;
	default:
		break;
	}

	// Update the input class
	pInput->Update();
}

void CCore::AddPlayer(EPlayers player, CPlayer &givenPlayer)
{
	if (pPlayer[player] == nullptr)
		pPlayer[player] = &givenPlayer;
}

void CCore::AddBullet(CBullet &givenBullet)
{
	pActiveBullets.push_back(&givenBullet);
}

void CCore::RemoveBullet(CBullet & givenBullet)
{
	for(unsigned int i = 0; i < pActiveBullets.size(); ++i)
	{
		if (pActiveBullets[i] == &givenBullet)
		{
			pActiveBullets.erase(pActiveBullets.begin() + i);
			return;
		}
	}
}

void CCore::AddEnemy(CTestEnemy &givenEnemy)
{
	mEnemyList.push_back(&givenEnemy);
}

void CCore::RemoveEnemy(CTestEnemy & givenEnemy)
{
	for (int i = 0; i < mEnemyList.size(); ++i)
	{
		if (mEnemyList[i] == &givenEnemy)
			mEnemyList.erase(mEnemyList.begin() + i);
	}
}

void CCore::LoadLevel(const char* levelName)
{
	FlashLoadScreen();

	// Level
	pLevel->LoadLevel(levelName); // test: "Levels\\TestLevel"

	// Player
	SVector2D<float> spawnPos = pLevel->GetSpawnPos();
	pPlayer[EPlayers::PlayerTeam] = new CPlayer(EPlayers::PlayerTeam, spawnPos.x, spawnPos.y, G_SPRITE_LAYER_Z_POS[ESpriteLayers::Player]);
	mGameState = EGameState::Playing;

	// Update UI
	pGUI->UpdateHealth(3);
	pGUI->SetWeaponHidden(false);
}

void CCore::UnloadGame()
{
	FlashLoadScreen();

	// unload bullets
	while (pActiveBullets.size() > 0)
		if (pActiveBullets[0] != NULL)
			pActiveBullets[0]->Remove();
		else
			cout << "NULL bullet found, bullet was removed incorrectly." << endl;

	// unload powerups
	while (pPowerUps.size() > 0)
		if (pPowerUps[pPowerUps.size() - 1] != NULL)
		{
			delete pPowerUps[pPowerUps.size() - 1];
			pPowerUps.pop_back();
		}

	// unload player
	if (pPlayer[EPlayers::PlayerTeam] != NULL)
	{
		delete pPlayer[EPlayers::PlayerTeam];
		pPlayer[EPlayers::PlayerTeam] = NULL;
	}

	// unload level
	//pLevel->UnloadLevel();
}

void CCore::SetupMenu()
{
	FlashLoadScreen();

	// Setup the menu elemetns
	pBackgroundSprite = new CWorldSprite("TemporyBG.png", { 1000.0f, 1000.0f }, BLEND_NORMAL);
	pBackgroundSprite->ResizeSprite(12.5f);
	pBackgroundSprite->ResizeX(1.777f);

	// Play button setup
	SUIData playButtonData;
	playButtonData.mSpritePaths.push_back("ButtonLeft.png");
	playButtonData.mSpritePaths.push_back("ButtonMiddle.png");
	playButtonData.mSpritePaths.push_back("ButtonRight.png");
	playButtonData.mHoverSpritePaths.push_back("ButtonLeft.png");
	playButtonData.mHoverSpritePaths.push_back("ButtonMiddleHover.png");
	playButtonData.mHoverSpritePaths.push_back("ButtonRight.png");
	playButtonData.mSpriteXSize = 3;
	playButtonData.mSize = { 125, 45 };
	playButtonData.mPosition = { 1000.0f, 300.0f };
	pPlayButton = new CButton(&playButtonData, "Play Game");

	// Put the camera in the correct place
	pCamera->SetX(1000.0f);
	pCamera->SetY(1000.0f);

	// Unlock the mouse
	pTLEngine->StopMouseCapture();

	mGameState = EGameState::MainMenu;
}

void CCore::UnloadMenu()
{
	FlashLoadScreen();

	delete pBackgroundSprite;
	delete pPlayButton;
}

void CCore::FlashLoadScreen()
{
	// Create the load screen model
	//CWorldSprite* pLoadScreen = new CWorldSprite("Black.png", { -1000.0f, -1000.0f }, BLEND_NORMAL);
	//pLoadScreen->ResizeSprite(256.0f);

	// Store the camera coords
	SVector3D<float> cameraPos = { pCamera->GetX(),  pCamera->GetY(),  pCamera->GetZ() };
	// Set a tempory position for this camera
	pCamera->SetPosition(-1000.0f, -1000.0f, cameraPos.z);

	// Force a draw call so we can display this
	// We'll do 2 so that any text on screen will not display
	pTLEngine->DrawScene();
	pText[0]->Draw("Loading", pTLEngine->GetWidth() / 2, pTLEngine->GetHeight() / 2, kBlack, kCentre, kVCentre);
	pTLEngine->DrawScene();

	// Set the camera back to where it was
	pCamera->SetPosition(cameraPos.x, cameraPos.y, cameraPos.z);

	// Clean up the load screen
	//delete pLoadScreen;
}
