// CLevel.cpp 02-03-2018
// William John Atkin WJAtkin@UCLan.ac.uk
#include "BUILD_ORDER.h"

CLevel::CLevel()
{
	// Sets the pointers
	mpEngine = CCore::GetInstance()->GetTLEngine();
	mpInput = CCore::GetInstance()->GetInput();

	// Creates the highlight sprite
	cursorHighlightSprite = new CWorldSprite(highlightSpriteName, DEFAULT_SPRITE_POS);

	// Creates a grid

}

CLevel::~CLevel()
{

}

void CLevel::Update()
{
	// Pans the camera
	tle::ICamera* camera = CCore::GetInstance()->GetCamera();
	CInput* inputHandle = CCore::GetInstance()->GetInput();
	float* deltaTime = CCore::GetInstance()->GetFrameTimer();
	if (inputHandle->KeyHeld(PAN_UP))
	{
		camera->MoveLocalY((*deltaTime) * CAMERA_PAN_SPEED);
	}
	else if (inputHandle->KeyHeld(PAN_Down))
	{
		camera->MoveLocalY(-(*deltaTime) * CAMERA_PAN_SPEED);
	}
	if (inputHandle->KeyHeld(PAN_RIGHT))
	{
		camera->MoveLocalX((*deltaTime) * CAMERA_PAN_SPEED);
	}
	else if (inputHandle->KeyHeld(PAN_LEFT))
	{
		camera->MoveLocalX(-(*deltaTime) * CAMERA_PAN_SPEED);
	}

	// Checks if the mouse is in the level window
	SVector2D<float> mousePos = { static_cast<float>(mpEngine->GetMouseX()), static_cast<float>(mpEngine->GetMouseY()) };
	if (mousePos.x >= minPos.x && mousePos.x <= maxPos.x)
	{
		if (mousePos.y >= minPos.y && mousePos.y <= maxPos.y)
		{
			// Updates position of the highlight tile
			SVector2D<float> tilePos = findCursorTilePos();
			cursorHighlightSprite->SetPosition({ tilePos.x, tilePos.y });
			cursorHighlightSprite->SetZ(DEFAULT_SPRITE_POS.z);
		}
		else
		{
			// Updates z position of the highlight tile
			cursorHighlightSprite->SetZ(HIDE_Z_POS);
		}
	}
	else
	{
		// Updates z position of the highlight tile
		cursorHighlightSprite->SetZ(HIDE_Z_POS);
	}

}

SVector2D<float> CLevel::findCursorTilePos()
{
	// Finds the mouse pixel position
	SVector2D<float> mousePos = { static_cast<float>(mpEngine->GetMouseX()), static_cast<float>(mpEngine->GetMouseY()) };
	// Gets where the center of the screen is
	tle::ICamera* camera = CCore::GetInstance()->GetCamera();
	SVector2D<float> screenPos = { camera->GetX(), camera->GetY() };
	SVector2D<int> windowSize = CCore::GetInstance()->GetWindowSize();
	SVector2D<float> worldSpace;

	// Finds the position in world space
	worldSpace.x = screenPos.x + (mousePos.x - static_cast<float>(windowSize.x / 2.0f)) / PIXELS_PER_METER;
	worldSpace.y = screenPos.y - (mousePos.y - static_cast<float>(windowSize.y / 2.0f)) / PIXELS_PER_METER;

	worldSpace.x += 0.5f;
	worldSpace.y += 0.5f;

	// Convert it to the grid
	worldSpace.x = floorf(worldSpace.x);
	worldSpace.y = floorf(worldSpace.y);


	return worldSpace;
}