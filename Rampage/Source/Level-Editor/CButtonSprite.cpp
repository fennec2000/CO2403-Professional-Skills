// CButtonSprite.cpp 08-03-2018
// William John Atkin WJAtkin@UCLan.ac.uk
#include "BUILD_ORDER.h"

CButtonSprite::CButtonSprite(const char* pSpriteName, const char* pHoverSpriteName, SVector3D<float> position, SVector2D<float> size)
{
	CalculateColisionBox({ position.x, position.y }, size);

	// Spawn the sprites in
	mpNormalSprite = CCore::GetInstance()->GetTLEngine()->CreateSprite(pSpriteName, position.x, position.y, position.z);
	mpHoverSprite = CCore::GetInstance()->GetTLEngine()->CreateSprite(pHoverSpriteName, position.x, position.y, HIDE_Z_POS);

	mOrigin = position;
}

CButtonSprite::CButtonSprite(const char* pSpriteName, const char* pHoverSpriteName, SVector2D<float> position, SVector2D<float> size)
{
	CalculateColisionBox(position, size);

	// Spawn the sprites in
	mpNormalSprite = CCore::GetInstance()->GetTLEngine()->CreateSprite(pSpriteName, position.x, position.y, DEFAULT_Z_POS - 0.1f);
	mpHoverSprite = CCore::GetInstance()->GetTLEngine()->CreateSprite(pHoverSpriteName, position.x, position.y, HIDE_Z_POS);

	mOrigin = { position.x, position.y, DEFAULT_Z_POS - 0.1f };
}

CButtonSprite::~CButtonSprite() 
{ 
	CCore::GetInstance()->GetTLEngine()->RemoveSprite(mpNormalSprite);
	CCore::GetInstance()->GetTLEngine()->RemoveSprite(mpHoverSprite);
}

bool CButtonSprite::CheckClick()
{
	tle::I3DEngine* pEngine = CCore::GetInstance()->GetTLEngine();

	// Gets mouse pos
	SVector2D<int> mousePos = { pEngine->GetMouseX(), pEngine->GetMouseY() };

	// Checks for hit
	if (mousePos.x >= minPos.x && mousePos.x <= maxPos.x)
	{
		if (mousePos.y >= minPos.y && mousePos.y <= maxPos.y)
		{
			if (CCore::GetInstance()->GetInput()->KeyHit(Mouse_LButton))
			{
				return true;
			}
			else
			{
				ShowHoverSprite();
				return false;
			}
		}
	}
	ShowNormalSprite();
	return false;
}

void CButtonSprite::ChangeSprites(const char* pSpriteName, const char* pHoverSpriteName)
{
	tle::I3DEngine* pEngine = CCore::GetInstance()->GetTLEngine();

	pEngine->RemoveSprite(mpNormalSprite);
	pEngine->RemoveSprite(mpHoverSprite);

	mpNormalSprite = pEngine->CreateSprite(pSpriteName, mOrigin.x, mOrigin.y, DEFAULT_Z_POS - 0.1f);
	mpHoverSprite = pEngine->CreateSprite(pHoverSpriteName, mOrigin.x, mOrigin.y, HIDE_Z_POS);
}

void CButtonSprite::CalculateColisionBox(SVector2D<float> position, SVector2D<float> size)
{
	minPos.x = static_cast<int>(position.x);
	maxPos.x = static_cast<int>(position.x + size.x);

	minPos.y = static_cast<int>(position.y);
	maxPos.y = static_cast<int>(position.y + size.y);
}

void CButtonSprite::ShowHoverSprite()
{
	if (!hoverVisable)
	{
		mpNormalSprite->SetZ(HIDE_Z_POS);
		mpHoverSprite->SetZ(DEFAULT_Z_POS - 0.1f);

		hoverVisable = true;
	}
}

void CButtonSprite::ShowNormalSprite()
{
	if (hoverVisable)
	{
		mpHoverSprite->SetZ(HIDE_Z_POS);
		mpNormalSprite->SetZ(DEFAULT_Z_POS - 0.1f);

		hoverVisable = false;
	}
}