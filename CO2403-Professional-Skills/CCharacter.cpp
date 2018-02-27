
#include "BUILD_ORDER.h"

CCharacter::CCharacter()
{
	mpC = CCore::GetInstance();
	mpTLEngine = mpC->GetTLEngine();
	mpFrameTimer = mpC->GetFrameTimer();
	mpCharSprite = new CWorldSprite("UglyTile.png", { 5.0f, 0.1f, 5.0f });
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

	if (mCheatGod)
		return;

	mHealthCurrent += change;
}