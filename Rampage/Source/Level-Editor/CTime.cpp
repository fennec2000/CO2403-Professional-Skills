// CTime.cpp 02/03/2018
// William John Atkin WJAtkin@UCLan.ac.uk
#pragma once
#include "BUILD_ORDER.h"

const float CTime::GAME_SPEED = 1.0f;
float CTime::mDeltaTime = 0.0f;

CTime::CTime() { }

void CTime::UpdateDeltaTime(tle::I3DEngine* pPassedEngine)
{
	mDeltaTime = pPassedEngine->Timer();
}

float CTime::AdjustedGameTime()
{
	return mDeltaTime * GAME_SPEED;
}