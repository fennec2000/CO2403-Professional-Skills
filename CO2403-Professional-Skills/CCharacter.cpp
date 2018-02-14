
#include "BUILD_ORDER.h"

CCharacter::CCharacter()
{
	mpC = CCore::GetInstance();
	mpTLEngine = mpC->GetTLEngine();
	mpFrameTimer = mpC->GetFrameTimer();
	mpCharSprite = new CWorldSprite("UglyTile.png", { 5.0f, 0.1f, 5.0f });
}

CCharacter::~CCharacter()
{

}
