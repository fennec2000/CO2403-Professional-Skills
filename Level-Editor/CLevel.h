// CLevel.h 02-03-2018
// William John Atkin WJAtkin@UCLan.ac.uk
#include "BUILD_ORDER.h"
#pragma once

class CLevel
{
public:
	CLevel();
	~CLevel();

	// Called once per frame
	void Update();

	// IO
	void ExportLevel();
	void LoadLevel();

	// Building Utills
	void ChangeSelectedTile(ETileType tileType);
	
	// Map genration and unloading
	void GenerateMap();
	void UnloadMap();

	static const SVector2D<int> MAP_MAX_SIZE;

private:
	SVector2D<float> findCursorTilePos();
	void GenerateSprite(const char* pSpriteName, SVector2D<int> position);

	// Map data
	SMapData mMapData;
	vector<vector<CWorldSprite*>*> levelSprites;

	ETileType currentlySelectedTile = NO_TILE;

	// Level pan controls
	const tle::EKeyCode PAN_UP = tle::Key_W;
	const tle::EKeyCode PAN_Down = tle::Key_S;
	const tle::EKeyCode PAN_LEFT = tle::Key_A;
	const tle::EKeyCode PAN_RIGHT = tle::Key_D;
	const float CAMERA_PAN_SPEED = 10.0f;

	const float PIXELS_PER_METER = 37.0f;

	// Variables for making sure the mouse is in the level window
	SVector2D<int> minPos = { 0, 72 };
	SVector2D<int> maxPos = { 960, 720 };
	const float HIDE_Z_POS = -25.0f;
	const float LEVEL_TILE_Z_POS = 0.01f;

	// Pointers to input and engine
	tle::I3DEngine* mpEngine;
	CInput* mpInput;

	// Cursor highlight sprite
	const char* HIGHLIGHT_SPRITE_NAME = "BlueTrans.png";
	const char* HIGHLIGHT_OUT_OF_BOUNDS_SPRITE_NAME = "RedTrans.png";
	const SVector3D<float> DEFAULT_SPRITE_POS = { 0.0f, 0.0f, 0.0f };
	CWorldSpriteMul* cursorHighlightSprite;

	// Level offset from camera
	SVector2D<float> offSet;
};
