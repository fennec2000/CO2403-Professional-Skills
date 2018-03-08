// CWorldSprite.cpp 12-02-2018
// William John Atkin WJAtkin@UCLan.ac.uk
#include "BUILD_ORDER.h"

// Inits the static variables
int CWorldSprite::mInstanceCount = 0;
tle::IMesh* CWorldSprite::mpMesh = nullptr;

// Constructers
CWorldSprite::CWorldSprite(const char* pSpriteName, SVector3D<float> position)
{
	// Sets the variables
	mOrigin = { position.x, position.y, position.z };

	// Checks if this is the first instance
	if (mInstanceCount == 0)
	{
		// Loads the mesh in
		mpMesh = CCore::GetInstance()->GetTLEngine()->LoadMesh(SPRITE_WORLD_MODEL);
	}

	// Creates the model
	mpSpriteModel = mpMesh->CreateModel(mOrigin.x, mOrigin.y, mOrigin.z);
	mpSpriteModel->RotateLocalZ(180.0f); // Rotates the sprites the correct way up

	// Sets the skin
	mpSpriteModel->SetSkin(pSpriteName);

	// Incrementation
	mInstanceCount++;
}

CWorldSprite::CWorldSprite(const char* pSpriteName, SVector2D<float> position)
{
	// Sets the variables
	mOrigin = { position.x, position.y, DEFAULT_Z_POS };

	// Checks if this is the first instance
	if (mInstanceCount == 0)
	{
		// Loads the mesh in
		mpMesh = CCore::GetInstance()->GetTLEngine()->LoadMesh(SPRITE_WORLD_MODEL);
	}

	// Creates the model
	mpSpriteModel = mpMesh->CreateModel(mOrigin.x, mOrigin.y, mOrigin.z);
	mpSpriteModel->RotateLocalZ(180.0f); // Rotates the sprites the correct way up

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
		CCore::GetInstance()->GetTLEngine()->RemoveMesh(mpMesh);
	}

	// Decrementation
	mInstanceCount--;
}

// Lookat functions
void CWorldSprite::LookAt(tle::ISceneNode* target)
{
	LookAt(target->GetX(), target->GetY(), target->GetZ());
}

void CWorldSprite::LookAt(CWorldSprite* target)
{
	LookAt(target->GetX(), target->GetY(), target->GetZ());
}

void CWorldSprite::LookAt(SVector3D<float> target)
{
	LookAt(target.x, target.y, target.z);
}

void CWorldSprite::LookAt(float fX, float fY, float fZ)
{
	// Calculates matrix axes for this sprite
	// Gets the facing (z) vector from positions
	SVector3D<float> vectorZ = (SVector3D<float>(fX, fY, fZ) - GetPosition3D()).Normalised();
	// Uses cross product to get the other axes
	// Must be normalised first
	SVector3D<float> vectorX = SVector3D<float>::CrossProduct(&maths::Y_AXIS_VECTOR, &vectorZ).Normalised();
	SVector3D<float> vectorY = SVector3D<float>::CrossProduct(&vectorZ, &vectorX).Normalised();

	// Builds the matrix from axes & position row by row
	SMatrix4x4 dummyMat;
	dummyMat.MakeIdentity();
	dummyMat.SetRow(0, vectorX);
	dummyMat.SetRow(1, vectorY);
	dummyMat.SetRow(2, vectorZ);
	dummyMat.SetRow(3, GetPosition3D());

	// Sets the matrix of this sprite
	mpSpriteModel->SetMatrix(&dummyMat.e00);

	// Rotates the sprite by 180 on its local X and Z axis so 
	// that it is facing the corect direction
	float mat[4][4];
	mpSpriteModel->GetMatrix(&mat[0][0]);
	if (mat[2][0] >= 0.0f)
	{
		mpSpriteModel->RotateLocalY(90.0f);
	}
	else
	{
		mpSpriteModel->RotateLocalY(270.0f);
	}
	mpSpriteModel->RotateLocalX(180.0f);
	mpSpriteModel->RotateLocalZ(90.0f);
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
	mOffset.x = 0.0f;
	mOrigin.x = newX;
	mpSpriteModel->SetLocalX(mOrigin.x + mOffset.x);
}

void CWorldSprite::SetY(float newY)
{
	mOffset.y = 0.0f;
	mOrigin.y = newY;
	mpSpriteModel->SetLocalY(mOrigin.y + mOffset.y);
}

void CWorldSprite::SetZ(float newZ)
{
	mOffset.z = 0.0f;
	mOrigin.z = newZ;
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

// By rotation
void CWorldSprite::RotateZ(float amount)
{
	mpSpriteModel->RotateLocalZ(amount);
}

void CWorldSprite::ResetZRot()
{
	mpSpriteModel->ResetOrientation();
	mpSpriteModel->RotateLocalZ(180.0f);
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

// Spirte utills
void CWorldSprite::SetSpriteSkin(const char* pSpriteName)
{
	mpSpriteModel->SetSkin(pSpriteName);
}