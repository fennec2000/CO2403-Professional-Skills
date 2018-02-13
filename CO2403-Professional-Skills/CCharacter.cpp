#include "CCharacter.h"

CCharacter::CCharacter()
{
	mC = CCore::getInstance();
	mpTLEngine = mC->getTLEngine();
	mpCharSprite = new CWorldSprite(mpTLEngine, "UglyTile.png", { 5.0f, 0.1f, 5.0f });
}

CCharacter::~CCharacter()
{

}
