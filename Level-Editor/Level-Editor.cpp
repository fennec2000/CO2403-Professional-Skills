// Level-Editor.cpp: A program using the TL-Engine
#include "BUILD_ORDER.h"
using namespace tle;

void main()
{
	// Creates the Core
	CCore* pCore = CCore::GetInstance();

	/**** Set up your scene here ****/


	// The main game loop, repeat until engine is stopped
	while (pCore->GetTLEngine()->IsRunning())
	{
		// Draw the scene
		pCore->UpdateCore();

		/**** Update your scene each frame here ****/

		if (pCore->GetInput()->KeyHit(Key_Escape))
			pCore->GetTLEngine()->Stop();
	}
}
