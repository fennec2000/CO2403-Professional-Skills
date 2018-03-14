// CTime.h 02/03/2018
// William John Atkin WJAtkin@UCLan.ac.uk
#pragma once
#include "BUILD_ORDER.h"

class CTime
{
public:
	// Updates delta time variable with the time it took to complete the last frame
	static void UpdateDeltaTime(tle::I3DEngine* pPassedEngine);

	// Returns the result of deltaTime * game speed
	static float AdjustedGameTime();

private:
	CTime();

	// The initilisation of these is in the .cpp file
	static const float GAME_SPEED; 	// The speed of the game, 1.0f is 1 second per second
	static float mDeltaTime; // Updates every frame
};
