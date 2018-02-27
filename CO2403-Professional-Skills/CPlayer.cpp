#include "BUILD_ORDER.h"

CPlayer::CPlayer(EPlayers player)
{
	mpC->AddPlayer(player, *this);
}

CPlayer::CPlayer(EPlayers player, float x, float y, float z)
{
	mpC->AddPlayer(player, *this);
	SetPosition(x, y, z);
}

CPlayer::~CPlayer()
{

}

void CPlayer::Update()
{
	InputCheck();
}

void CPlayer::InputCheck()
{
	if (mpTLEngine->KeyHeld(mPlayerMoveUp))
	{
		mpCharSprite->MoveY(mMoveSpeed * *mpFrameTimer);
	}
	if (mpTLEngine->KeyHeld(mPlayerMoveLeft))
	{
		mpCharSprite->MoveX(-mMoveSpeed * *mpFrameTimer);
	}
	if (mpTLEngine->KeyHeld(mPlayerMoveDown))
	{
		mpCharSprite->MoveY(-mMoveSpeed * *mpFrameTimer);
	}
	if (mpTLEngine->KeyHeld(mPlayerMoveRight))
	{
		mpCharSprite->MoveX(mMoveSpeed * *mpFrameTimer);
	}
}

void CPlayer::Death()
{

}