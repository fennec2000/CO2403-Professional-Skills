#include "BUILD_ORDER.h"

// Setup instance
CCore* CCore::mInstance = 0;

CCore* CCore::GetInstance()
{
	if (mInstance == 0)
	{
		mInstance = new CCore();
	}

	return mInstance;
}

CCore::CCore()
{
	// Load engine
	mTLEngine = New3DEngine(kTLX);

	// Engine settings
	mTLEngine->StartWindowed();
	mTLEngine->AddMediaFolder("TestMedia");

	// Data setup
	for (int i = 0; i < EPlayers::NumOfEPlayers; ++i)
		mpPlayer[i] = nullptr;
}

void CCore::UpdateCore()
{
	// Draw the scene
	mFrameTime = mTLEngine->Timer();	// update the frame timer
	mTLEngine->DrawScene();				// draw the frame 
}

void CCore::AddPlayer(EPlayers player, CPlayer &givenPlayer)
{
	if (mpPlayer[player] == nullptr)
		mpPlayer[player] = &givenPlayer;
}