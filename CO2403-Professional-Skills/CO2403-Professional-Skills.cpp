// CO2403-Professional-Skills.cpp: A program using the TL-Engine
//
#include "BUILD_ORDER.h"
using namespace tle;

// Golbal variables, used so that the core is not passed around between functions
CCore* gpCore;

void main()
{
	// For leak dectection
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Create core and set the global pointer to it
	gpCore = CCore::GetInstance();

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
