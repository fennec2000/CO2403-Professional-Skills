#pragma once
#include <TL-Engine.h>
#include "CCore.h"
// This class has the base functions that both the player and enemies have

class CCharacter
{
private:
	CCore* mC;
	tle::I3DEngine* mTLEngine;
	tle::IModel* mModel;
public:
	CCharacter();
	~CCharacter();

	void SetPos(float x, float y, float z) { mModel->SetPosition(x, y, z); };
	void SetScale(float size) { mModel->Scale(size); };

	void SetLookAt(float x, float y, float z) { mModel->LookAt(x, y, z); };
	void SetLookAt(ISceneNode* target) { mModel->LookAt(target); };
};