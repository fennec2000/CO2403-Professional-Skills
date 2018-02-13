#include "CPlayer.h"

CPlayer::CPlayer()
{

}

CPlayer::CPlayer(float x, float y, float z)
{
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
		mpCharSprite->MoveZ(mMoveSpeed * *mpFrameTimer);
	}
	if (mpTLEngine->KeyHeld(mPlayerMoveLeft))
	{
		mpCharSprite->MoveX(-mMoveSpeed * *mpFrameTimer);
	}
	if (mpTLEngine->KeyHeld(mPlayerMoveDown))
	{
		mpCharSprite->MoveZ(-mMoveSpeed * *mpFrameTimer);
	}
	if (mpTLEngine->KeyHeld(mPlayerMoveRight))
	{
		mpCharSprite->MoveX(mMoveSpeed * *mpFrameTimer);
	}
}