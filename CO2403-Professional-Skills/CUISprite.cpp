// CUISprite.cpp 12-02-2018
// William John Atkin WJAtkin@UCLan.ac.uk

#include "BUILD_ORDER.h"

// Constructers
CUISprite::CUISprite(const char* pSpriteName, SVector3D<float> position)
{
	mpSprite = CCore::getInstance()->getTLEngine()->CreateSprite(pSpriteName, position.x, position.y, position.z);
	mOrigin = position;
}

CUISprite::CUISprite(const char* pSpriteName, SVector2D<float> position)
{
	mpSprite = CCore::getInstance()->getTLEngine()->CreateSprite(pSpriteName, position.x, position.y, DEFAULT_Z_POS);
	mOrigin = { position.x, position.y, DEFAULT_Z_POS };
}

// Destructer
CUISprite::~CUISprite()
{
	CCore::getInstance()->getTLEngine()->RemoveSprite(mpSprite);
}

// For sprite movement
// By translation
void CUISprite::Move(SVector3D<float> moveAmount)
{
	MoveX(moveAmount.x);
	MoveY(moveAmount.y);
	MoveZ(moveAmount.z);
}

void CUISprite::Move(SVector2D<float> moveAmount)
{
	MoveX(moveAmount.x);
	MoveY(moveAmount.y);
}

void CUISprite::MoveX(float moveAmount)
{
	mOffset.x += moveAmount;
	mpSprite->SetX(mOrigin.x + mOffset.x);
}

void CUISprite::MoveY(float moveAmount)
{
	mOffset.y += moveAmount;
	mpSprite->SetY(mOrigin.y + mOffset.y);
}

void CUISprite::MoveZ(float moveAmount)
{
	mOffset.z += moveAmount;
	mpSprite->SetZ(mOrigin.z + mOffset.z);
}

// By setting
void CUISprite::SetPosition(SVector3D<float> moveAmount)
{
	mOffset = moveAmount;
	mpSprite->SetPosition(mOffset.x, mOffset.y);
	mpSprite->SetZ(mOffset.z);
}

void CUISprite::SetPosition(SVector2D<float> moveAmount)
{
	mOffset = { moveAmount.x, moveAmount.y, mOffset.z };
	mpSprite->SetPosition(mOffset.x, mOffset.y);
}

void CUISprite::SetX(float newX)
{
	mOffset.x = newX;
	mpSprite->SetX(mOffset.x);
}

void CUISprite::SetY(float newY)
{
	mOffset.y = newY;
	mpSprite->SetY(mOffset.y);
}

void CUISprite::SetZ(float newZ)
{
	mOffset.z = newZ;
	mpSprite->SetZ(mOffset.z);
}

// By resetting
void CUISprite::ResetPosition()
{
	mOffset.x = 0.0f;
	mOffset.y = 0.0f;
	mOffset.z = 0.0f;

	mpSprite->SetPosition(mOrigin.x, mOrigin.y);
	mpSprite->SetZ(mOrigin.z);
}

// Getters
SVector3D<float> CUISprite::GetPosition3D()
{
	SVector3D<float> position;
	position.x = mOrigin.x + mOffset.x;
	position.y = mOrigin.y + mOffset.y;
	position.z = mOrigin.z + mOffset.z;
	return position;
}

SVector2D<float> CUISprite::GetPosition2D()
{
	SVector2D<float> position;
	position.x = mOrigin.x + mOffset.x;
	position.y = mOrigin.y + mOffset.y;
	return position;
}

float CUISprite::GetX()
{
	return mOrigin.x + mOffset.x;
}

float CUISprite::GetY()
{
	return mOrigin.y + mOffset.y;
}

float CUISprite::GetZ()
{
	return mOrigin.z + mOffset.z;
}
