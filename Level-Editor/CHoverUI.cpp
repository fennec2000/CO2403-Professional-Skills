// CHoverUI.cpp 02/03/2018
// William John Atkin WJAtkin@UCLan.ac.uk
#pragma once
#include "BUILD_ORDER.h"

CHoverUI::CHoverUI(SUIData* pUIData)
{
	mpMyEngine = CCore::GetInstance()->GetTLEngine();
	mpInput = CCore::GetInstance()->GetInput();
	mSpritePaths = pUIData->mSpritePaths;
	mHoverSpritePaths = pUIData->mHoverSpritePaths;

	// Calculates the min and max x and y positions
	mMinPos = pUIData->mPosition;
	mMaxPos.x = pUIData->mPosition.x + pUIData->mSize.x;
	mMaxPos.y = pUIData->mPosition.y + pUIData->mSize.y;

	// Generate the normal sprites
	// Left hand sprite
	tle::ISprite* pNewSprite = mpMyEngine->CreateSprite(pUIData->mSpritePaths[0], pUIData->mPosition.x, pUIData->mPosition.y, mDefaultZPos);
	mSprites.push_back(pNewSprite);
	// Middle sprites
	for (int i = pUIData->mSpriteXSize; i < pUIData->mSize.x - pUIData->mSpriteXSize; i++)
	{
		pNewSprite = mpMyEngine->CreateSprite(pUIData->mSpritePaths[1], pUIData->mPosition.x + i, pUIData->mPosition.y);
		mSprites.push_back(pNewSprite);
	}
	// Right hand sprite
	pNewSprite = mpMyEngine->CreateSprite(pUIData->mSpritePaths[2], pUIData->mPosition.x + pUIData->mSize.x - pUIData->mSpriteXSize, pUIData->mPosition.y);
	mSprites.push_back(pNewSprite);

	// Generate the hover sprites
	// Left hand sprite
	pNewSprite = mpMyEngine->CreateSprite(pUIData->mHoverSpritePaths[0], pUIData->mPosition.x, pUIData->mPosition.y, HIDE_Z_POS);
	mHoverSprites.push_back(pNewSprite);
	// Middle sprites
	for (int i = pUIData->mSpriteXSize; i < pUIData->mSize.x - pUIData->mSpriteXSize; i++)
	{
		pNewSprite = mpMyEngine->CreateSprite(pUIData->mHoverSpritePaths[1], pUIData->mPosition.x + i, pUIData->mPosition.y);
		mHoverSprites.push_back(pNewSprite);
	}
	// Right hand sprite
	pNewSprite = mpMyEngine->CreateSprite(pUIData->mHoverSpritePaths[2], pUIData->mPosition.x + pUIData->mSize.x - pUIData->mSpriteXSize, pUIData->mPosition.y);
	mHoverSprites.push_back(pNewSprite);
}

CHoverUI::~CHoverUI()
{
}

bool CHoverUI::Update()
{
	// Gets the mouse position
	float mouseX = static_cast<float>(mpMyEngine->GetMouseX());
	float mouseY = static_cast<float>(mpMyEngine->GetMouseY());

	if (mouseX >= mMinPos.x && mouseX <= mMaxPos.x)
	{
		if (mouseY >= mMinPos.y && mouseY <= mMaxPos.y)
		{
			ShowHoverSprites();
			if (mpInput->KeyHit(tle::Mouse_LButton))
			{
				return true;
			}
		}
	}

	ShowNormalSprites();
	return false;
}

void CHoverUI::DeleteThis()
{
	for (unsigned int i = 0; i < mSprites.size(); i++)
	{
		mpMyEngine->RemoveSprite(mSprites[i]);
	}
}

void CHoverUI::SetEnabled(bool enable)
{

}

void CHoverUI::ShowNormalSprites()
{
	for (unsigned int i = 0; i < mSprites.size(); i++)
	{
		mSprites[i]->SetZ(mDefaultZPos);
		mHoverSprites[i]->SetZ(HIDE_Z_POS);
	}
}

void CHoverUI::ShowHoverSprites()
{
	for (unsigned int i = 0; i < mSprites.size(); i++)
	{
		mSprites[i]->SetZ(HIDE_Z_POS);
		mHoverSprites[i]->SetZ(mDefaultZPos);
	}
}