// CO2403-Professional-Skills.cpp: A program using the TL-Engine
//
#include "BUILD_ORDER.h"
using namespace tle;

// Golbal variables, used so that the core is not passed around between functions
CCore* gpCore;

void main(int argc, char* argv[])
{
	// For leak dectection
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Check if we have come from the level editor
	if (argc > 1)
	{
		// In the event an external program, i.e. our level editor has started the .exe
		// we need to ensure our wokring directory is updated
		SetCurrentDirectory("..\\CO2403-Professional-Skills");

		// Create core and set the global pointer to it
		gpCore = CCore::GetInstance();

		// We can determine that argv[1] will be the map file that we need to load
		// We also need to bypass the games front end and load up the level staigt away
		gpCore->BypassFrontEnd(argv[1]);
	}
	else
	{
		// Create core and set the global pointer to it
		gpCore = CCore::GetInstance();
	}
  
	// The main program loop, repeat until the user wishes to exit
	// In this case when the user wishes to exit we will shut the
	// engine down
	while (gpCore->GetTLEngine()->IsRunning())
	{
		gpCore->UpdateCore();
	}
  
	// Cleanup
	delete gpCore;
}
