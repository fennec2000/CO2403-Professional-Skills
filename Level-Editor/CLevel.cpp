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
	SVector2D<float> mousePos = findCursorTilePos();

	std::cout << "Mouse pos: x: " << mousePos.x << " y:" << mousePos.y << "\n";

	// Updates position of the highlight tile
	cursorHighlightSprite->SetPosition({ static_cast<float>(mousePos.x), static_cast<float>(mousePos.y) });
}

SVector2D<float> CLevel::findCursorTilePos()
{
	// Finds the mouse pixel position
	SVector2D<int> mousePos = { mpEngine->GetMouseX(), mpEngine->GetMouseY() };
	// Gets where the center of the screen is
	tle::ICamera* camera = CCore::GetInstance()->GetCamera();
	SVector2D<float> screenPos = { camera->GetX(), camera->GetY() };

	SVector2D<float> worldSpace;

	// Finds the position on the grid
	worldSpace.x = floorf(static_cast<float>(mousePos.x) / METERS_PER_PIXEL);
	worldSpace.y = floorf(static_cast<float>(mousePos.y) / METERS_PER_PIXEL);

	return worldSpace;
}