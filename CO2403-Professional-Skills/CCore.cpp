#include "CCore.h"

// Setup instance
CCore* CCore::mInstance = 0;

CCore* CCore::getInstance()
{
	if (mInstance == 0)
	{
		mInstance = new CCore();
	}

	return mInstance;
}

CCore::CCore()
{
	// Load engine
	mTLEngine = New3DEngine(kTLX);

	// Engine settings
	mTLEngine->StartWindowed();
	mTLEngine->AddMediaFolder("TestMedia");

	// Setup extra data
	mQuadMesh = mTLEngine->LoadMesh("quad.x");
	//mQuadMesh = mTLEngine->LoadMesh("cube.x");
}