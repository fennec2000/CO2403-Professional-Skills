// CO2403-Professional-Skills.cpp: A program using the TL-Engine

#include "BUILD_ORDER.h"
#include "CPlayer.h"	// the player class
#include "CCore.h"		// singleton class
using namespace tle;

// global sprite layers floats
enum ESpriteLayers { Floor, Enemy, Player, UI, NumOfESpriteLayers };
const float G_SPRITE_LAYER_Y_POS[ESpriteLayers::NumOfESpriteLayers] = { 0.1f, 0.2f, 0.3f, 1.0f };

// Tempory Keys
EKeyCode G_PAN_FORWARDS = Key_W;
EKeyCode G_PAN_BACKWARDS = Key_S;
EKeyCode G_PAN_RIGHT = Key_D;
EKeyCode G_PAN_LEFT = Key_A;
EKeyCode G_PAN_OUT = Key_Q;
EKeyCode G_PAN_IN = Key_E;
EKeyCode G_EXIT = Key_Escape;

// Tempory speed
const float G_GAME_SPEED = 1.0f;
const float G_UI_MOVE_SPEED = 10.0f;

void main()
{
	// Creat core
	CCore* c = CCore::getInstance();

	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = c->getTLEngine();

	/**** Set up your scene here ****/
	// Player
	CPlayer* pThePlayer = new CPlayer(0.0f, G_SPRITE_LAYER_Y_POS[ESpriteLayers::Player], 0.0f);
	// Player test values

	// Monster
	CTestEnemy* mMonster = new CTestEnemy(3.0f, G_SPRITE_LAYER_Y_POS[ESpriteLayers::Enemy], 0.0f, true);

	// Camera
	ICamera* myCamera = myEngine->CreateCamera(kManual);
	myCamera->RotateX(90.0f);
	myCamera->SetPosition(5.0f, 10.0f, 5.0f);

	// Creates test sprite
	CWorldSprite* pWorldSprite;
	pWorldSprite = new CWorldSprite("UpArrow.png", { 1.0f, G_SPRITE_LAYER_Y_POS[ESpriteLayers::Floor], 1.0 });

	// Monster Test
	CWorldSprite* mWorldSprite;
	mWorldSprite = new CWorldSprite("derp.png", { 1.0f, G_SPRITE_LAYER_Y_POS[ESpriteLayers::Enemy], 1.0 });

	float* deltaTime = c->getFrameTimer();
	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// CCore update - this calls both draw frame and update frame time
		c->UpdateCore();

		// player update
		pThePlayer->Update();

		/**** Update your scene each frame here ****/

		// keybindings for camera
		if (myEngine->KeyHeld(G_PAN_FORWARDS))
		{
			myCamera->MoveZ(G_UI_MOVE_SPEED * *deltaTime * G_GAME_SPEED);
		}
		else if (myEngine->KeyHeld(G_PAN_BACKWARDS))
		{
			myCamera->MoveZ(-G_UI_MOVE_SPEED * *deltaTime * G_GAME_SPEED);
		}
		if (myEngine->KeyHeld(G_PAN_RIGHT))
		{
			myCamera->MoveX(G_UI_MOVE_SPEED * *deltaTime * G_GAME_SPEED);
		}
		else if (myEngine->KeyHeld(G_PAN_LEFT))
		{
			myCamera->MoveX(-G_UI_MOVE_SPEED * *deltaTime * G_GAME_SPEED);
		}
		if (myEngine->KeyHeld(G_PAN_IN))
		{
			myCamera->MoveY(-G_UI_MOVE_SPEED * *deltaTime * G_GAME_SPEED);
		}
		else if (myEngine->KeyHeld(G_PAN_OUT))
		{
			myCamera->MoveY(G_UI_MOVE_SPEED * *deltaTime * G_GAME_SPEED);
		}

		// For testing sprites look at;
		if (myEngine->KeyHit(Key_9))
		{
			pWorldSprite->LookAt(myCamera);
		}

		if (myEngine->KeyHit(G_EXIT))
		{
			myEngine->Stop();
		}
	}
  
	// Cleanup
	delete pThePlayer;
	delete pWorldSprite;

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}