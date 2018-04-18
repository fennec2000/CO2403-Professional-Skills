// CInput.h 05-02-2018
// William John Atkin WJAtkin@UCLan.ac.uk

#pragma once
#include "BUILD_ORDER.h"

class CInput
{
public:
	// Constructer
	CInput(tle::I3DEngine* pPassedEngine);

	// MUST be called once per frame
	void Update();

	// For checking if keys are hit
	bool KeyHit(tle::EKeyCode key);
	std::vector<tle::EKeyCode> GetKeysHit();

	// For checking if keys are held
	bool KeyHeld(tle::EKeyCode key);
	std::vector<tle::EKeyCode> GetKeysHeld();

private:
	tle::I3DEngine* mpMyEngine;

	std::vector<bool> mKeyHitStates;
	std::vector<bool> mKeyHeldStates;
};