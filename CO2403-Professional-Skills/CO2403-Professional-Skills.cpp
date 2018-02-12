// CO2403-Professional-Skills.cpp: A program using the TL-Engine

#include "BUILD_ORDER.h"
using namespace tle;

// Tempory Keys
EKeyCode G_PAN_FORWARDS = Key_W;
EKeyCode G_PAN_BACKWARDS = Key_S;
EKeyCode G_PAN_RIGHT = Key_D;
EKeyCode G_PAN_LEFT = Key_A;
EKeyCode G_EXIT = Key_Escape;

// Tempory speed
const float G_GAME_SPEED = 1.0f;
const float G_UI_MOVE_SPEED = 250.0f;

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine( kTLX );
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder( "C:\\ProgramData\\TL-Engine\\Media" );
	myEngine->AddMediaFolder( "TestMedia" );

	/**** Set up your scene here ****/
	CUISprite* artUI = new CUISprite(myEngine, "AnArt.png", { 20.0f, 50.0f } );

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
			artUI->MoveY(G_UI_MOVE_SPEED * deltaTime * G_GAME_SPEED);
		}
		else if (myEngine->KeyHeld(G_PAN_BACKWARDS))
		{
			artUI->MoveY(-G_UI_MOVE_SPEED * deltaTime * G_GAME_SPEED);
		}
		if (myEngine->KeyHeld(G_PAN_RIGHT))
		{
			artUI->MoveX(G_UI_MOVE_SPEED * deltaTime * G_GAME_SPEED);
		}
		else if (myEngine->KeyHeld(G_PAN_LEFT))
		{
			artUI->MoveX(-G_UI_MOVE_SPEED * deltaTime * G_GAME_SPEED);
		}

		if (myEngine->KeyHit(G_EXIT))
		{
			myEngine->Stop();
		}
	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
