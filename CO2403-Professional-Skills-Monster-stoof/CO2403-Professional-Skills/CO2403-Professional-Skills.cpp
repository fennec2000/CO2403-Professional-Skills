// CO2403-Professional-Skills.cpp: A program using the TL-Engine
//
#include "BUILD_ORDER.h"
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
	// Level test
	c->GetLevel()->LoadLevel("Levels\\TestLevel");
	SVector2D<float> spawnPos = c->GetLevel()->GetSpawnPos();

	// Player
	CPlayer* pThePlayer = new CPlayer(EPlayers::PlayerTeam, spawnPos.x, spawnPos.y, G_SPRITE_LAYER_Z_POS[ESpriteLayers::Player]);
	// Player test values



	// Monster
	//CTestEnemy* mMonster = new CTestEnemy(3.0f, 0, 0.0f, true);
	//CEnemyShotgun* mShotgun = new CEnemyShotgun(20.0f, 5, 0.0f, true);
	//CEnemyChaingun* mChaingun = new CEnemyChaingun(18.0f, 5, 0.0f, true);

	


	// Monster Test
	CWorldSprite* mWorldSprite;
	mWorldSprite = new CWorldSprite("derp.png", { spawnPos.x + 1.0f, spawnPos.y, G_SPRITE_LAYER_Z_POS[ESpriteLayers::Enemy]});

	float* deltaTime = c->GetFrameTimer();

	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// CCore update - this calls both draw frame and update frame time
		c->UpdateCore();

		// player update
		pThePlayer->Update();

		/**** Update your scene each frame here ****/

		// exit key
		if (myEngine->KeyHit(G_EXIT))
		{
			myEngine->Stop();
		}
	}
  
	// Cleanup
	delete pThePlayer;

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}