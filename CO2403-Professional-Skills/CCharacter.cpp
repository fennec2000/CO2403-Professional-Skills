
#include "BUILD_ORDER.h"

CCharacter::CCharacter()
{
	mpC = CCore::getInstance();
	mpTLEngine = mpC->getTLEngine();
	mpFrameTimer = mpC->getFrameTimer();
	mpCharSprite = new CWorldSprite("UglyTile.png", { 5.0f, 0.1f, 5.0f });
}

CCharacter::~CCharacter()
{

}
