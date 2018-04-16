#pragma once
#include "BUILD_ORDER.h"

const int MAX_HEARTS = 3;
const float HEALTH_SPACING = 75.0f;
const float OFFSCREEN = -1000.0f;
const SVector2D<float> HEALTH_OFFSET = { 10, 10 };

class CGUI
{
private:
	CUISprite* pHeartSprites[MAX_HEARTS];
	bool heartHidden[MAX_HEARTS] = { false, false, false }; // false = visable, true = hidden
	int health;

	void UpdateUIPos(int heart);
	void SetHiddenHeart(int heart);
public:
	CGUI();
	virtual ~CGUI();
	void UpdateHealth(int health);
	void TakeDamage(int damage);
};

