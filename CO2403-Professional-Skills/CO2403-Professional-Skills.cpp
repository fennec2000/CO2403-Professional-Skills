// CO2403-Professional-Skills.cpp: A program using the TL-Engine
//
#include "BUILD_ORDER.h"
using namespace tle;

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

	// Create an animation for testing
	vector<const char*> animatedSprites;
	animatedSprites.push_back("wallServer1.png");
	animatedSprites.push_back("wallServer2.png");
	animatedSprites.push_back("wallServer3.png");
	animatedSprites.push_back("wallServer4.png");
	animatedSprites.push_back("wallServer5.png");
	animatedSprites.push_back("wallServer6.png");
	//CAnimatedWorldSprite* animatedSprite = new CAnimatedWorldSprite(animatedSprites, { spawnPos.x - 7.0f, spawnPos.y,  G_SPRITE_LAYER_Z_POS[ESpriteLayers::Floor] });

	// Monster Test
	CWorldSprite* mWorldSprite;
	SVector2D<float> spawnPos = c->GetLevel()->GetSpawnPos();
	mWorldSprite = new CWorldSprite("derp.png", { spawnPos.x + 1.0f, spawnPos.y, G_SPRITE_LAYER_Z_POS[ESpriteLayers::Enemy]});

	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// CCore update - this calls both draw frame and update frame time
		c->UpdateCore();

		//animatedSprite->Update();
	}
  
	// Cleanup
	delete c;

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}