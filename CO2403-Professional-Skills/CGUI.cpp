#include "CGUI.h"



CGUI::CGUI()
{
	health = MAX_HEARTS;

	for (int i = 0; i < MAX_HEARTS; i++)
	{
		SVector2D<float> hpPos = HEALTH_OFFSET;
		hpPos.x += HEALTH_SPACING * i;
		pHeartSprites[i] = new CUISprite("Heart.png", hpPos);
	}
}


CGUI::~CGUI()
{
	// remove hearts
	for (int i = 0; i < MAX_HEARTS; i++)
		delete pHeartSprites[i];
}

void CGUI::UpdateUIPos(int heart)
{
	if (heart < MAX_HEARTS && heart >= 0)
	{
		SVector2D<float> newPos = HEALTH_OFFSET;
		newPos.x += (HEALTH_SPACING * heart);
		pHeartSprites[heart]->SetPosition(newPos);
		heartHidden[heart] = false;
	}
}

void CGUI::SetHiddenHeart(int heart)
{
	if (heart < MAX_HEARTS && heart >= 0)
	{
		pHeartSprites[heart]->SetPosition(SVector2D<float>(-1000, -1000));
		heartHidden[heart] = true;
	}
}

void CGUI::UpdateHealth(int givenHealth)
{
	if (givenHealth > MAX_HEARTS)
		health = MAX_HEARTS;
	else if (givenHealth < 0)
		health = 0;
	else
		health = givenHealth;

	for (int i = 0; i < health; i++)
	{
		if (heartHidden[i])
			UpdateUIPos(i);
	}

	for (int i = health; i < MAX_HEARTS; i++)
	{
		if (!heartHidden[i])
			SetHiddenHeart(i);
	}
}

void CGUI::TakeDamage(int damage)
{
	health -= damage;

	// check for overkill
	if (health < 0)
		health = 0;

	// update the UI
	UpdateHealth(health);
}
