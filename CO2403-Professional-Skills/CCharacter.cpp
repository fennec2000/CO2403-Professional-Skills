#include "CCharacter.h"

CCharacter::CCharacter()
{
	mC = CCore::getInstance();
	mTLEngine = mC->getTLEngine();
	mModel = mC->getQuadMesh()->CreateModel();
}

CCharacter::~CCharacter()
{

}
