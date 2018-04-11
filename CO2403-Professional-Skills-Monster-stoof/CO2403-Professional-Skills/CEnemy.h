#include "BUILD_ORDER.h"
#ifndef CENEMY_H
#define CENEMY_H


class CEnemy : protected CCharacter 
{
public:
	virtual void Update() = 0;
	virtual void Death() = 0;
	virtual void toggleActive() = 0;
	virtual void Shoot() = 0;
};

#endif