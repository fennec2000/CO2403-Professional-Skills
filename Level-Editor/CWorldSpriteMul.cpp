// CWorldSpriteMul.h 11-03-2018
// William John Atkin WJAtkin@UCLan.ac.uk
#include "BUILD_ORDER.h"

// Inits the static variables
int CWorldSpriteMul::mInstanceCountMul = 0;
tle::IMesh* CWorldSpriteMul::mpMeshMul = nullptr;

CWorldSpriteMul::CWorldSpriteMul(const char* pSpriteName, SVector3D<float> position)
{
	// Sets the variables
	mOrigin = { position.x, position.y, position.z };

	// Checks if this is the first instance
	if (mInstanceCountMul == 0)
	{
		// Loads the mesh in
		mpMeshMul = CCore::GetInstance()->GetTLEngine()->LoadMesh(SPRITE_MODEL_NAME);
	}

	// Creates the model
	mpSpriteModel = mpMeshMul->CreateModel(mOrigin.x, mOrigin.y, mOrigin.z);
	mpSpriteModel->RotateLocalZ(180.0f); // Rotates the sprites the correct way up

	// Sets the skin
	mpSpriteModel->SetSkin(pSpriteName);

	// Incrementation
	mInstanceCountMul++;
}

CWorldSpriteMul::CWorldSpriteMul(const char* pSpriteName, SVector2D<float> position)
{
	// Sets the variables
	mOrigin = { position.x, position.y, DEFAULT_Z_POS };

	// Checks if this is the first instance
	if (mInstanceCountMul == 0)
	{
		// Loads the mesh in
		mpMeshMul = CCore::GetInstance()->GetTLEngine()->LoadMesh(SPRITE_MODEL_NAME);
	}

	// Creates the model
	mpSpriteModel = mpMeshMul->CreateModel(mOrigin.x, mOrigin.y, mOrigin.z);
	mpSpriteModel->RotateLocalZ(180.0f); // Rotates the sprites the correct way up

	// Sets the skin
	mpSpriteModel->SetSkin(pSpriteName);

	// Incrementation
	mInstanceCountMul++;
}

CWorldSpriteMul::~CWorldSpriteMul()
{
	// Clean up
	mpMeshMul->RemoveModel(mpSpriteModel);

	// Checks if this is the last instance
	if (mInstanceCountMul == 1)
	{
		// Removes the mesh to finish clean up
		CCore::GetInstance()->GetTLEngine()->RemoveMesh(mpMeshMul);
	}

	// Decrementation
	mInstanceCountMul--;
}

void CWorldSpriteMul::SetUp()
{
	mSpriteWorldModel = strdup(SPRITE_MODEL_NAME);
}