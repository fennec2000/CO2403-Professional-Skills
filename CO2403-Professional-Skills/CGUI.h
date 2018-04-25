#pragma once
#include "BUILD_ORDER.h"

enum EWeapons { Default, Shotgun };

const int MAX_HEARTS = 3;
const float HEALTH_SPACING = 75.0f;
const float OFFSCREEN = -1000.0f;
const SVector2D<float> HEALTH_OFFSET = { 10, 10 }; // offset from top left
const int WEAPONS_ICONS_COUNT = 2;
const int WEAPON_ICON_OFFSET[2] = { 15, 79 }; // ofset from bottom left
const int WEAPON_TEXT_OFFSET[2] = { 80, 50 }; // ofset from bottom left

class CGUI
{
private:
	const char* WEAPON_ICONS_NAMES[WEAPONS_ICONS_COUNT] = { "GunIcon.png", "ShotgunIcon.png" };

	CUISprite* pHeartSprites[MAX_HEARTS];
	CUISprite* pWeaponIcon;
	CUISprite* pWeaponBG;
	IFont* pText[EFontTypes::NumOfFontTypes];
	bool heartHidden[MAX_HEARTS] = { false, false, false }; // false = visable, true = hidden
	int health;
	int height;
	int width;

	void SetHiddenHeart(int heart);
	void UpdateUIPos(int heart);
public:
	CGUI(int givenHeight, int givenWidth);
	virtual ~CGUI();
	void UpdateHealth(int health);
	void TakeDamage(int damage);
	void SetWeaponHidden(bool hide);
	void SetWeaponIcon(EWeapons newWeapon);
	void Update();
};

