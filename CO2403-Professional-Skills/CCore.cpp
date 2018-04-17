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

	// Load engine
	pTLEngine = New3DEngine(kTLX);

	// Engine settings
	pTLEngine->StartWindowed();
	//pTLEngine->StartFullscreen();
	pTLEngine->AddMediaFolder("TestMedia");
	pTLEngine->AddMediaFolder("Media");

	// Font
	for(int i = 0; i < EFontTypes::NumOfFontTypes; i++)
		pText[i] = pTLEngine->LoadFont("Lucida Sans", mTEXT_SIZE[i]);

	// Camera
	pCamera = pTLEngine->CreateCamera(kManual, 0.0f, 0.0f, -20.0f);

	// GUI
	pGUI = new CGUI();

	// Data setup
	for (int i = 0; i < EPlayers::NumOfEPlayers; ++i)
		pPlayer[i] = nullptr;

	// set playing
	mGameState = EGameState::MainMenu;
	mGameScore = 0;

	// Creates the level
	pLevel = new CLevel();
}

CCore::~CCore()
{
	if (pPlayer[EPlayers::PlayerTeam] != NULL)
	{
		delete pPlayer[EPlayers::PlayerTeam];
		pPlayer[EPlayers::PlayerTeam] = NULL;
	}

	delete pGUI;
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
		LoadLevel();
		break;
	case Playing:
		// level update
		pLevel->Update();

		// player update
		pPlayer[EPlayers::PlayerTeam]->Update();

		for (int i = 0; i < pActiveBullets.size(); ++i)
		{
			if (pActiveBullets[i] != NULL)
			{
				pActiveBullets[i]->Update();
				//if (pActiveBullets[i]->returnTeam() == EnemyTeam)
				//{
				//	SVector2D<float> bulletPos = pActiveBullets[i]->GetPos2D();
				//	SVector2D<float> playerPos = GetPlayer(PlayerTeam)->GetPos2D();
				//	float distance = sqrt(((playerPos.x - bulletPos.x) * (playerPos.x - bulletPos.x)) + ((playerPos.y - bulletPos.y) * (playerPos.y - bulletPos.y)));
				//	if (distance < pActiveBullets[i]->getSize())
				//	{
				//		pActiveBullets[i]->Remove();
				//	}
				//}
				//else if (pActiveBullets[i]->returnTeam() == PlayerTeam)
				//{
				//	// do stuff
				//}
			}
			else
				cout << "invalid BULLET" << endl;
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
			mGameState = EGameState::MainMenu;
		}
		break;
	default:
		break;
	}
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
	for(int i = 0; i < pActiveBullets.size(); ++i)
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
	// Level
	pLevel->LoadLevel(levelName); // test: "Levels\\TestLevel"

	// Player
	SVector2D<float> spawnPos = pLevel->GetSpawnPos();
	pPlayer[EPlayers::PlayerTeam] = new CPlayer(EPlayers::PlayerTeam, spawnPos.x, spawnPos.y, G_SPRITE_LAYER_Z_POS[ESpriteLayers::Player]);
	mGameState = EGameState::Playing;
}

void CCore::UnloadGame()
{
	// unload bullets
	while (pActiveBullets.size() > 0)
		if (pActiveBullets[0] != NULL)
			pActiveBullets[0]->Remove();
		else
			cout << "NULL bullet found, bullet was removed incorrectly." << endl;


	// unload player
	if (pPlayer[EPlayers::PlayerTeam] != NULL)
	{
		delete pPlayer[EPlayers::PlayerTeam];
		pPlayer[EPlayers::PlayerTeam] = NULL;
	}

	// unload level
	pLevel->UnloadLevel();
}


