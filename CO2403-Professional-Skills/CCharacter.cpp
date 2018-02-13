#include "CCharacter.h"

CCharacter::CCharacter()
{
	mpC = CCore::getInstance();
	mpTLEngine = mpC->getTLEngine();
	mpFrameTimer = mpC->getFrameTimer();
	mpCharSprite = new CWorldSprite(mpTLEngine, "UglyTile.png", { 5.0f, 0.1f, 5.0f });
}

CCharacter::~CCharacter()
{

}
