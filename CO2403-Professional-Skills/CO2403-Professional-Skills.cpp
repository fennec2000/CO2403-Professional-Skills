// CO2403-Professional-Skills.cpp: A program using the TL-Engine

#include "BUILD_ORDER.h"
#include "CPlayer.h"	// the player class
#include "CCore.h"		// singleton class
using namespace tle;


// Tempory Keys
EKeyCode G_EXIT = Key_Escape;


void main()
{
	// Creat core
	CCore* c = CCore::GetInstance();

	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = c->GetTLEngine();

	/**** Set up your scene here ****/
	// Player
	CPlayer* pThePlayer = new CPlayer(EPlayers::Player1, 0.0f, G_SPRITE_LAYER_Z_POS[ESpriteLayers::UI], 0);
	// Player test values


	// Monster
	CTestEnemy* mMonster = new CTestEnemy(3.0f, 0, 0.0f, true);

	// Temp sprites
	vector<CWorldSprite*> pSprites;
	for (int i = 0; i < 10; i ++)
	{
		for (int j = 0; j < 10; j ++)
		{
			pSprites.push_back(new CWorldSprite("Floor.png", { static_cast<float>(i), static_cast<float>(j), G_SPRITE_LAYER_Z_POS[ESpriteLayers::Floor] }));
		}
	}


	// Monster Test
	CWorldSprite* mWorldSprite;
	mWorldSprite = new CWorldSprite("derp.png", { 1.0f, 0, 1.0 });

	float* deltaTime = c->GetFrameTimer();


	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// CCore update - this calls both draw frame and update frame time
		c->UpdateCore();

		// player update
		pThePlayer->Update();
		mMonster->Update();

		/**** Update your scene each frame here ****/

		// exit key
		if (myEngine->KeyHit(G_EXIT))
		{
			myEngine->Stop();
		}
	}
  
	// Cleanup
	delete pThePlayer;
	for (int i = 0; i < pSprites.size(); i++)
	{
		delete (pSprites.back());
		pSprites.pop_back();
	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}