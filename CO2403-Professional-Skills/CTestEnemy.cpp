#include "BUILD_ORDER.h"

CTestEnemy::CTestEnemy()
{

}

CTestEnemy::CTestEnemy(float x, float y, float z, bool activate)
{
	SetPosition(x, y, z);
	isActive = activate;
}

CTestEnemy::~CTestEnemy()
{

}

void CTestEnemy::Update()
{
	
}