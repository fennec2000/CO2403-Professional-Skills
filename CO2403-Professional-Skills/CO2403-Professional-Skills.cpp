// CO2403-Professional-Skills.cpp: A program using the TL-Engine

#include "BUILD_ORDER.h"
//#include "CPlayer.h"	// the player class
//#include "CCore.h"		// singleton class
using namespace tle;

// global sprite layers floats
enum ESpriteLayers { Floor, Enemy, Player, UI, NumOfESpriteLayers = 4};
const float G_SPRITE_LAYER_Z_POS[ESpriteLayers::NumOfESpriteLayers] = {  1.0f, 0.3f, 0.2f, 0.1f };

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
	CCore* c = CCore::GetInstance();

	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = c->GetTLEngine();

	/**** Set up your scene here ****/
	// Level test
	CLevel::LoadLevelFromMapFile("testMap1.txt");
	SVector2D<float> spawnPos = CLevel::GetSpawnPos();

	// Player
	CPlayer* pThePlayer = new CPlayer(EPlayers::Player1, spawnPos.x, spawnPos.y, G_SPRITE_LAYER_Z_POS[ESpriteLayers::Player]);
	// Player test values

	// Camera
	ICamera* myCamera = myEngine->CreateCamera(kManual, spawnPos.x, spawnPos.y, -20.0f);

	float* deltaTime = c->GetFrameTimer();
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
			myCamera->MoveY(G_UI_MOVE_SPEED * *deltaTime * G_GAME_SPEED);
		}
		else if (myEngine->KeyHeld(G_PAN_BACKWARDS))
		{
			myCamera->MoveY(-G_UI_MOVE_SPEED * *deltaTime * G_GAME_SPEED);
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
			myCamera->MoveZ(G_UI_MOVE_SPEED * *deltaTime * G_GAME_SPEED);
		}
		else if (myEngine->KeyHeld(G_PAN_OUT))
		{
			myCamera->MoveZ(-G_UI_MOVE_SPEED * *deltaTime * G_GAME_SPEED);
		}

		if (myEngine->KeyHit(G_EXIT))
		{
			myEngine->Stop();
		}
	}
  
	// Cleanup
	delete pThePlayer;
	//for (int i = 0; i < pSprites.size(); i++)
	//{
	//	delete (pSprites.back());
	//	pSprites.pop_back();
	//}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}