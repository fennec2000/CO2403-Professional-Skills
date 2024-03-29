#include "BUILD_ORDER.h"

// Setup instance
CCore* CCore::pInstance = 0;

CCore* CCore::GetInstance()
{
	if (pInstance == 0)
	{
		new CCore();
	}

	return pInstance;
}

CCore::CCore()
{
	// Set the pointer
	pInstance = this;

	// Load engine
	pTLEngine = New3DEngine(kTLX);

	// Engine settings
	pTLEngine->StartWindowed(mWindowSize.x, mWindowSize.y);
	pTLEngine->SetWindowCaption("Level Editor");
	pTLEngine->AddMediaFolder("Media");
	pTLEngine->AddMediaFolder("EditorMedia");
	pTLEngine->AddMediaFolder("Media\\WallServerAnimated");

	// Camera
	pCamera = pTLEngine->CreateCamera(kManual, 0.0f, 0.0f, -20.0f);

	// Data setup
	for (int i = 0; i < EPlayers::NumOfEPlayers; ++i)
		pPlayer[i] = nullptr;

	// set playing
	mGameState = EGameState::Playing;
	mGameScore = 0;

	// Creates the level
	mpLevel = new CLevel();

	// Creates the input handling syste,
	mpInput = new CInput(pTLEngine);
}

void CCore::UpdateCore()
{
	// Draw the scene
	mFrameTime = pTLEngine->Timer();	// update the frame timer
	mpInput->Update();					// Update key inputs
	pTLEngine->DrawScene();				// draw the frame

	// Calls update on other classes
	mpLevel->Update();

	//for (std::vector<CEProjectile*>::iterator it = eBullets.begin(); it != eBullets.end(); it++)
	//{
	//	(*it)->Update();
	//	if ((*it)->getLifetime() > 2.9f)
	//	{
	//		delete(*it);
	//		eBullets.erase((it));
	//		it = eBullets.begin();
	//	}
    //}
}

void CCore::AddPlayer(EPlayers player, CPlayer &givenPlayer)
{
	if (pPlayer[player] == nullptr)
		pPlayer[player] = &givenPlayer;
}

void CCore::AddBullet(float ex, float ey, float ez)
{
	//eBullets.push_back(new CEProjectile(ex, ey, ez));
}

void CCore::updateBullets()
{
  
}