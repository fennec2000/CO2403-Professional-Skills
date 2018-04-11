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
	pTLEngine->AddMediaFolder("TestMedia");
	pTLEngine->AddMediaFolder("Media");
	pTLEngine->AddMediaFolder("Media\\Animation");

	// Camera
	pCamera = pTLEngine->CreateCamera(kManual, 0.0f, 0.0f, -20.0f);

	// GUI
	pGUI = new CGUI();

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
	pLevel->Update();
	
	for (int i = 0; i < pActiveBullets.size(); ++i)
	{
		if (pActiveBullets[i] != NULL)
		{
			pActiveBullets[i]->Update();
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
				// do stuff
			}

		}
		else
			cout << "invalid BULLET" << endl;
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
