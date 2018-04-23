#include "BUILD_ORDER.h"



CPowerShotgun::CPowerShotgun(SVector2D<float> spawnPos) :CPowerUp()
{

	pWorldSprite = new CWorldSprite("ShotgunIcon.png", SVector3D<float>(spawnPos.x, spawnPos.y, G_SPRITE_LAYER_Z_POS[Player]), BLEND_CUTOUT);
};


CPowerShotgun::~CPowerShotgun()
{

}
