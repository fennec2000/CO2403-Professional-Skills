// CWorldSprite.cpp 12-02-2018
// William John Atkin WJAtkin@UCLan.ac.uk

#include "BUILD_ORDER.h"

// Inits the static variables
int CWorldSprite::mInstanceCount = 0;
tle::IMesh* CWorldSprite::mpMesh = nullptr;

// Constructers
CWorldSprite::CWorldSprite(tle::I3DEngine* pEngine, const char* pSpriteName, SVector3D<float> position) : CBaseSprite(pEngine)
{
	// Sets the variables
	mpEngine = pEngine;
	mOrigin = { position.x, position.y, position.z };

	// Checks if this is the first instance
	if (mInstanceCount == 0)
	{
		// Loads the mesh in
		mpMesh = mpEngine->LoadMesh(SPRITE_WORLD_MODEL);
	}

	// Creates the model
	mpSpriteModel = mpMesh->CreateModel(mOrigin.x, mOrigin.y, mOrigin.z);

	// Sets the size
	mpSpriteModel->Scale(0.1f);

	// Sets the skin
	mpSpriteModel->SetSkin(pSpriteName);

	// Incrementation
	mInstanceCount++;
}

CWorldSprite::CWorldSprite(tle::I3DEngine* pEngine, const char* pSpriteName, SVector2D<float> position) : CBaseSprite(pEngine)
{
	// Sets the variables
	mpEngine = pEngine;
	mOrigin = { position.x, position.y, DEFAULT_Z_POS };

	// Checks if this is the first instance
	if (mInstanceCount == 0)
	{
		// Loads the mesh in
		mpMesh = mpEngine->LoadMesh(SPRITE_WORLD_MODEL);
	}

	// Creates the model
	mpSpriteModel = mpMesh->CreateModel(mOrigin.x, mOrigin.y, mOrigin.z);

	// Sets the size
	mpSpriteModel->Scale(0.1f);

	// Sets the skin
	mpSpriteModel->SetSkin(pSpriteName);

	// Incrementation
	mInstanceCount++;
}

// Destructers
CWorldSprite::~CWorldSprite()
{
	// Clean up
	mpMesh->RemoveModel(mpSpriteModel);

	// Checks if this is the last instance
	if (mInstanceCount == 1)
	{
		// Removes the mesh to finish clean up
		mpEngine->RemoveMesh(mpMesh);
	}

	// Decrementation
	mInstanceCount--;
}

// For sprite movement
// By translation
void CWorldSprite::Move(SVector3D<float> moveAmount)
{
	MoveX(moveAmount.x);
	MoveX(moveAmount.y);
	MoveX(moveAmount.z);
}

void CWorldSprite::Move(SVector2D<float> moveAmount)
{
	MoveX(moveAmount.x);
	MoveX(moveAmount.y);
}

void CWorldSprite::MoveX(float moveAmount)
{
	mOffset.x += moveAmount;
	mpSpriteModel->SetLocalX(mOrigin.x + mOffset.x);
}

void CWorldSprite::MoveY(float moveAmount)
{
	mOffset.y += moveAmount;
	mpSpriteModel->SetLocalY(mOrigin.y + mOffset.y);
}

void CWorldSprite::MoveZ(float moveAmount)
{
	mOffset.z += moveAmount;
	mpSpriteModel->SetLocalZ(mOrigin.z + mOffset.z);
}

// By setting
void CWorldSprite::SetPosition(SVector3D<float> moveAmount)
{
	SetX(moveAmount.x);
	SetY(moveAmount.y);
	SetZ(moveAmount.z);
}

void CWorldSprite::SetPosition(SVector2D<float> moveAmount)
{
	SetX(moveAmount.x);
	SetY(moveAmount.y);
}

void CWorldSprite::SetX(float newX)
{
	mOffset.x = newX;
	mpSpriteModel->SetLocalX(mOrigin.x + mOffset.x);
}

void CWorldSprite::SetY(float newY)
{
	mOffset.y = newY;
	mpSpriteModel->SetLocalY(mOrigin.y + mOffset.y);
}

void CWorldSprite::SetZ(float newZ)
{
	mOffset.z = newZ;
	mpSpriteModel->SetLocalZ(mOrigin.z + mOffset.z);
}

// By resetting
void CWorldSprite::ResetPosition()
{
	mOffset.x = 0.0f;
	mOffset.y = 0.0f;
	mOffset.z = 0.0f;

	mpSpriteModel->SetPosition(mOrigin.x, mOrigin.y, mOrigin.z);
}

// Getters
SVector3D<float> CWorldSprite::GetPosition3D()
{
	SVector3D<float> position;
	position.x = mOrigin.x + mOffset.x;
	position.y = mOrigin.y + mOffset.y;
	position.z = mOrigin.z + mOffset.z;
	return position;
}

SVector2D<float> CWorldSprite::GetPosition2D()
{
	SVector2D<float> position;
	position.x = mOrigin.x + mOffset.x;
	position.y = mOrigin.y + mOffset.y;
	return position;
}

float CWorldSprite::GetX()
{
	return mOrigin.x + mOffset.x;
}

float CWorldSprite::GetY()
{
	return mOrigin.y + mOffset.y;
}

float CWorldSprite::GetZ()
{
	return mOrigin.z + mOffset.z;
}
