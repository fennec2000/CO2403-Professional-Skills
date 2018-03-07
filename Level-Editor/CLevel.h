// CLevel.h 02-03-2018
// William John Atkin WJAtkin@UCLan.ac.uk
#include "BUILD_ORDER.h"
#pragma once

class CLevel
{
public:
	CLevel();
	~CLevel();

	void Update();

private:

	SVector2D<int> findCursorTilePos();

	vector<vector<ETileType>*> tileMap;

	// Level pan controls
	const tle::EKeyCode PAN_UP = tle::Key_W;
	const tle::EKeyCode PAN_Down = tle::Key_S;
	const tle::EKeyCode PAN_LEFT = tle::Key_A;
	const tle::EKeyCode PAN_RIGHT = tle::Key_D;

	const int METERS_PER_PIXEL = 50;

	// Pointers to input and engine
	tle::I3DEngine* mpEngine;
	CInput* mpInput;

	// Cursor highlight sprite
	const char* highlightSpriteName = "BlueTrans.png";
	const SVector3D<float> DEFAULT_SPRITE_POS = { 0.0f, 0.0f, -10.0f };
	CWorldSprite* cursorHighlightSprite;

	// Level offset from camera
	SVector2D<float> offSet;
};
