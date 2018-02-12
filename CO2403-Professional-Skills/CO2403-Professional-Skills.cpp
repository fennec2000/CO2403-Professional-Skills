// CO2403-Professional-Skills.cpp: A program using the TL-Engine

#include "BUILD_ORDER.h"
#include "CPlayer.h"
using namespace tle;

// Tempory Keys
EKeyCode G_PAN_FORWARDS = Key_W;
EKeyCode G_PAN_BACKWARDS = Key_S;
EKeyCode G_PAN_RIGHT = Key_D;
EKeyCode G_PAN_LEFT = Key_A;
EKeyCode G_PAN_OUT = Key_E;
EKeyCode G_PAN_IN = Key_Q;
EKeyCode G_EXIT = Key_Escape;

// Tempory speed
const float G_GAME_SPEED = 1.0f;
const float G_UI_MOVE_SPEED = 10.0f;

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine( kTLX );
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	//myEngine->AddMediaFolder( "C:\\ProgramData\\TL-Engine\\Media" );
	myEngine->AddMediaFolder( "TestMedia" );

	/**** Set up your scene here ****/
	CPlayer* pThePlayer = new CPlayer();
	ICamera* myCamera = myEngine->CreateCamera(kManual);
	myCamera->RotateX(90.0f);
	myCamera->SetPosition(5.0f, 10.0f, 5.0f);

	// Creates test sprites
	CWorldSprite* pWorldSprite; // for testing delete;
	const int testAmount = 10;
	for (int i = 0; i < testAmount; i++)
	{
		for (int j = 0; j < testAmount; j++)
		{
			pWorldSprite = new CWorldSprite(myEngine, "TestGrass.png", { static_cast<float>(i), 0.5f, static_cast<float>(j) });
		}
	}

	float deltaTime;
	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// Draw the scene
		deltaTime = myEngine->Timer();
		myEngine->DrawScene();

		/**** Update your scene each frame here ****/

		if (myEngine->KeyHeld(G_PAN_FORWARDS))
		{
			myCamera->MoveZ(G_UI_MOVE_SPEED * deltaTime * G_GAME_SPEED);
		}
		else if (myEngine->KeyHeld(G_PAN_BACKWARDS))
		{
			myCamera->MoveZ(-G_UI_MOVE_SPEED * deltaTime * G_GAME_SPEED);
		}
		if (myEngine->KeyHeld(G_PAN_RIGHT))
		{
			myCamera->MoveX(G_UI_MOVE_SPEED * deltaTime * G_GAME_SPEED);
		}
		else if (myEngine->KeyHeld(G_PAN_LEFT))
		{
			myCamera->MoveX(-G_UI_MOVE_SPEED * deltaTime * G_GAME_SPEED);
		}
		if (myEngine->KeyHeld(G_PAN_IN))
		{
			myCamera->MoveY(-G_UI_MOVE_SPEED * deltaTime * G_GAME_SPEED);
		}
		else if (myEngine->KeyHeld(G_PAN_OUT))
		{
			myCamera->MoveY(G_UI_MOVE_SPEED * deltaTime * G_GAME_SPEED);
			std::cout << myCamera->GetY() << std::endl;
		}

		// For testing if sprites can be deleted;
		if (myEngine->KeyHit(Key_9) && pWorldSprite != nullptr)
		{
			delete pWorldSprite;
			pWorldSprite = nullptr;
		}

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
