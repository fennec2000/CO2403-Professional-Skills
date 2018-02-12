#pragma once
#include <TL-Engine.h>
using namespace tle;
// Core file
// This holds data core to the game that needs to be passed arround

class CCore
{
private:
	//Here will be the instance stored.
	static CCore* mInstance;

	// Stored data
	I3DEngine* mTLEngine;
	IMesh* mQuadMesh;

	//Private constructor to prevent instancing.
	CCore();

public:
	//Static access method.
	static CCore* getInstance();

	// public functions
	I3DEngine* getTLEngine() { return mTLEngine; };
	IMesh* getQuadMesh() { return mQuadMesh; };
};