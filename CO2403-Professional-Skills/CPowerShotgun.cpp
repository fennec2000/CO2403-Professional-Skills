#include "BUILD_ORDER.h"



CPowerShotgun::CPowerShotgun(SVector2D<float> spawnPos):CPowerUp()
{
	pWorldSprite = new CWorldSprite("ShotgunIcon.png", spawnPos);
};


CPowerShotgun::~CPowerShotgun()
{

}
