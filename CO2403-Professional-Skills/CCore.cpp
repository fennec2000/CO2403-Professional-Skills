#include "BUILD_ORDER.h"

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
}

void CCore::UpdateCore()
{
	// Draw the scene
	mFrameTime = mTLEngine->Timer();	// update the frame timer
	mTLEngine->DrawScene();				// draw the frame 
}