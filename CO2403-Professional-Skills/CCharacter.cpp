
#include "BUILD_ORDER.h"

CCharacter::CCharacter()
{
	pC = CCore::GetInstance();
	pTLEngine = pC->GetTLEngine();
	pFrameTimer = pC->GetFrameTimer();
	pCharSprite = new CWorldSprite("UglyTile.png", { 5.0f, 0.1f, 5.0f }, BLEND_CUTOUT);
	mHealthMax = 1;
	mHealthCurrent = mHealthMax;
}

CCharacter::~CCharacter()
{

}

void CCharacter::ChangeHealth(int change)
{
	if (mHealthCurrent + change <= 0)
	{
		mHealthCurrent = 0;
		Death();
		return;
	}
	else if (mHealthCurrent + change > mHealthMax)
	{
		mHealthMax = mHealthMax;
		return;
	}

	mHealthCurrent += change;
}