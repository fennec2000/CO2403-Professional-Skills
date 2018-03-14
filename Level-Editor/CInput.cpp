// CInput.cpp 02/03/2018
// William John Atkin WJAtkin@UCLan.ac.uk
#pragma once
#include "BUILD_ORDER.h"

// Constructer
CInput::CInput(tle::I3DEngine* pPassedEngine)
{
	mpMyEngine = pPassedEngine;
}

// MUST be called once per frame
void CInput::Update()
{
	// Updates the hit key vector
	std::vector<bool> keyHitStatus;
	for (int i = 0; i < tle::kMaxKeyCodes; i++)
	{
		bool hit = mpMyEngine->KeyHit((tle::EKeyCode)i);
		if (hit)
		{
			keyHitStatus.push_back(true);
		}
		else
		{
			keyHitStatus.push_back(false);
		}
	}
	mKeyHitStates = keyHitStatus;

	// Updates the held key vector
	std::vector<bool> keyHeldStatus;
	for (int i = 0; i < tle::kMaxKeyCodes; i++)
	{
		bool hit = mpMyEngine->KeyHeld((tle::EKeyCode)i);
		if (hit)
		{
			keyHeldStatus.push_back(true);
		}
		else
		{
			keyHeldStatus.push_back(false);
		}
	}
	mKeyHeldStates = keyHeldStatus;
}

// For checking if keys are hit
bool CInput::KeyHit(tle::EKeyCode key)
{
	return mKeyHitStates[(int)key];
}
std::vector<tle::EKeyCode> CInput::GetKeysHit()
{
	std::vector<tle::EKeyCode> keysHit;
	for (int i = 0; i < tle::kMaxKeyCodes; i++)
	{
		if (mKeyHitStates[i] == true)
		{
			keysHit.push_back(static_cast<tle::EKeyCode>(i));
		}
	}

	return keysHit;
}

// For checking if keys are held
bool CInput::KeyHeld(tle::EKeyCode key)
{
	return mKeyHeldStates[(int)key];
}
std::vector<tle::EKeyCode> CInput::GetKeysHeld()
{
	std::vector<tle::EKeyCode> keysHeld;
	for (int i = 0; i < tle::kMaxKeyCodes; i++)
	{
		if (mKeyHeldStates[i] == true)
		{
			keysHeld.push_back(static_cast<tle::EKeyCode>(i));
		}
	}

	return keysHeld;
}