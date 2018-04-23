#pragma once
#include "BUILD_ORDER.h"


class CPowerShotgun : public CPowerUp
{
public:
	CPowerShotgun():CPowerUp() {};
	CPowerShotgun(SVector2D<float> spawnPos);
	virtual ~CPowerShotgun();
};

