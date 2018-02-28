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
	// Load engine
	pTLEngine = New3DEngine(kTLX);

	// Engine settings
	pTLEngine->StartWindowed();
	pTLEngine->AddMediaFolder("TestMedia");
	pTLEngine->AddMediaFolder("Media");

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
}

void CCore::UpdateCore()
{
	// Draw the scene
	mFrameTime = pTLEngine->Timer();	// update the frame timer
	pTLEngine->DrawScene();				// draw the frame 
}

void CCore::AddPlayer(EPlayers player, CPlayer &givenPlayer)
{
	if (pPlayer[player] == nullptr)
		pPlayer[player] = &givenPlayer;
}