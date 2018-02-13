#pragma once
#include "BUILD_ORDER.h"

using namespace tle;
// Core file
// This holds data core to the game that needs to be passed arround

class CCore
{
private:
	// Here will be the instance stored.
	static CCore* mInstance;

	// Stored data
	I3DEngine* mTLEngine;	// pointer to the tl engine
	float mFrameTime;		// time between each frame

	// Private constructor to prevent instancing.
	CCore();

public:
	//Static access method.
	static CCore* getInstance();

	// Public functions
	void UpdateCore();

	// Getters
	I3DEngine* getTLEngine() { return mTLEngine; };
	float* getFrameTimer() { return &mFrameTime; };

	// Setters
};