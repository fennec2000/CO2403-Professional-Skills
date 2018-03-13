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
	pLevel = new CLevel();
}

void CCore::UpdateCore()
{
	// Draw the scene
	mFrameTime = pTLEngine->Timer();	// update the frame timer
	pTLEngine->DrawScene();				// draw the frame 

	for (std::vector<CEProjectile*>::iterator it = eBullets.begin(); it != eBullets.end(); it++)
	{
		(*it)->Update();
		if ((*it)->getLifetime() > 2.9f)
		{
			delete(*it);
			eBullets.erase((it));
			it = eBullets.begin();
		}
	}

	for (int i = 0; i < pActiveBullets.size(); ++i)
	{
		if (pActiveBullets[i] != NULL)
		{
			pActiveBullets[i]->Update();
		}
		else
			cout << "invalid" << endl;
	}
}

void CCore::AddPlayer(EPlayers player, CPlayer &givenPlayer)
{
	if (pPlayer[player] == nullptr)
		pPlayer[player] = &givenPlayer;
}

void CCore::AddBullet(float ex, float ey, SVector2D<float> bulletVector)
{
	eBullets.push_back(new CEProjectile(ex, ey, 0, bulletVector));
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
