// CWorldSprite.cpp 12-02-2018
// William John Atkin WJAtkin@UCLan.ac.uk
#include "BUILD_ORDER.h"

// Inits the static variables
// Normal model
int CWorldSprite::mNormalInstanceCount = 0;
tle::IMesh* CWorldSprite::mpNormalMesh = nullptr;
// Cutout model
int CWorldSprite::mCutoutInstanceCount = 0;
tle::IMesh* CWorldSprite::mpCutoutMesh = nullptr;
// Multi model
int CWorldSprite::mMultiInstanceCount = 0;
tle::IMesh* CWorldSprite::mpMultiMesh = nullptr;

// Constructers
CWorldSprite::CWorldSprite() { }

CWorldSprite::CWorldSprite(const char* pSpriteName, SVector3D<float> position, ESpriteBlend blending)
{
	this->ConstructSprite(pSpriteName, position, blending);
}

CWorldSprite::CWorldSprite(const char* pSpriteName, SVector2D<float> position, ESpriteBlend blending)
{
	this->ConstructSprite(pSpriteName, { position.x, position.y, DEFAULT_Z_POS }, blending);
}

// Utill function for construtuctor
void CWorldSprite::ConstructSprite(const char* pSpriteName, SVector3D<float> position, ESpriteBlend blending)
{
	// Sets the variables
	mOrigin = position;
	blendingUsed = blending;

	IMesh* meshToUse = nullptr;
	switch (blending)
	{
	case BLEND_NORMAL:
		// Checks if this is the first instance
		if (mNormalInstanceCount == 0)
		{
			// Loads the mesh in
			mpNormalMesh = CCore::GetInstance()->GetTLEngine()->LoadMesh(SPRITE_WORLD_MODEL);
		}
		meshToUse = mpNormalMesh;
		++mNormalInstanceCount;
		break;
	case BLEND_CUTOUT:
		// Checks if this is the first instance
		if (mCutoutInstanceCount == 0)
		{
			// Loads the mesh in
			mpCutoutMesh = CCore::GetInstance()->GetTLEngine()->LoadMesh(SPRITE_WORLD_MODEL_CUTOUT);
		}
		meshToUse = mpCutoutMesh;
		++mCutoutInstanceCount;
		break;
	case BLEND_MULTIPLICATIVE:
		// Checks if this is the first instance
		if (mMultiInstanceCount == 0)
		{
			// Loads the mesh in
			mpMultiMesh = CCore::GetInstance()->GetTLEngine()->LoadMesh(SPRITE_WORLD_MODEL_MULTI);
		}
		meshToUse = mpMultiMesh;
		++mMultiInstanceCount;
		break;
	}

	// Creates the model
	mpSpriteModel = meshToUse->CreateModel(mOrigin.x, mOrigin.y, mOrigin.z);
	// Rotates the sprites the correct way up
	mpSpriteModel->RotateLocalZ(180.0f);
	// Sets the skin
	mpSpriteModel->SetSkin(pSpriteName);
}

// Destructers
CWorldSprite::~CWorldSprite()
{
	// Clean up
	switch (blendingUsed)
	{
	case BLEND_NORMAL:
		mpNormalMesh->RemoveModel(mpSpriteModel);

		// Checks if this is the last instance
		if (mNormalInstanceCount == 1)
		{
			// Removes the mesh to finish clean up
			CCore::GetInstance()->GetTLEngine()->RemoveMesh(mpNormalMesh);
		}

		// Decrementation
		--mNormalInstanceCount;
		break;
	case BLEND_CUTOUT:
		mpCutoutMesh->RemoveModel(mpSpriteModel);

		// Checks if this is the last instance
		if (mCutoutInstanceCount == 1)
		{
			// Removes the mesh to finish clean up
			CCore::GetInstance()->GetTLEngine()->RemoveMesh(mpCutoutMesh);
		}

		// Decrementation
		--mCutoutInstanceCount;
		break;
	case BLEND_MULTIPLICATIVE:
		mpMultiMesh->RemoveModel(mpSpriteModel);

		// Checks if this is the last instance
		if (mMultiInstanceCount == 1)
		{
			// Removes the mesh to finish clean up
			CCore::GetInstance()->GetTLEngine()->RemoveMesh(mpMultiMesh);
		}

		// Decrementation
		--mMultiInstanceCount;
		break;
	}
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

// Resizing
void CWorldSprite::ResizeSprite(float scalar)
{
	mpSpriteModel->ScaleX(scalar);
	mpSpriteModel->ScaleY(scalar);
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