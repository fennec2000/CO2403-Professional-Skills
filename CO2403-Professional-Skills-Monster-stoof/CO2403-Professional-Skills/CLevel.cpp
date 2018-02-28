// CLevel.h 20-02-2018
// William John Atkin WJAtkin@UCLan.ac.uk

#include "BUILD_ORDER.h"

CLevel::CLevel() { }

CLevel::~CLevel() { }

void CLevel::LoadLevelFromMapFile(const char* pFilePath)
{
	ReadFileToTileMap(pFilePath);
	GenerateLevel();
}

SVector2D<float> CLevel::GetSpawnPos()
{
	return mSpawnPos;
}

void CLevel::GenerateLevel()
{
	mWorldSprites = new vector<CWorldSprite*>;

	for (unsigned int i = 0; i < mTileMap->size(); i++)
	{
		for (unsigned int j = 0; j < mTileMap->at(i)->size(); j++)
		{
			float xAxis = static_cast<float>(j);
			float yAxis = static_cast<float>(i);

			if (mTileMap->at(i)->at(j) == NO_TILE)
			{
				// 0 is blank for now
				//mWorldSprites.push_back(new CWorldSprite("Floor.png", { i, j }));
			}
			else if (mTileMap->at(i)->at(j) == FLOOR)
			{
				mWorldSprites->push_back(new CWorldSprite("Floor.png", SVector3D<float>(xAxis, yAxis, G_SPRITE_LAYER_Z_POS[ESpriteLayers::Floor])));
			}
			else if (mTileMap->at(i)->at(j) == WALL)
			{
				mWorldSprites->push_back(new CWorldSprite("FullWall.png", SVector3D<float>(xAxis, yAxis, G_SPRITE_LAYER_Z_POS[ESpriteLayers::Floor])));
			}
			else if (mTileMap->at(i)->at(j) == WALL_WITH_SIDE)
			{
				mWorldSprites->push_back(new CWorldSprite("WallSide.png", SVector3D<float>(xAxis, yAxis, G_SPRITE_LAYER_Z_POS[ESpriteLayers::Floor])));
			}
			else if (mTileMap->at(i)->at(j) == WALL_WITH_SIDE_FLIPPED_Y)
			{
				mWorldSprites->push_back(new CWorldSprite("WallSide.png", SVector3D<float>(xAxis, yAxis, G_SPRITE_LAYER_Z_POS[ESpriteLayers::Floor])));
				mWorldSprites->back()->RotateZ(180.0f);
			}
			else if (mTileMap->at(i)->at(j) == SPAWN)
			{
				// This is a floor but will also serve as a spawn point
				mWorldSprites->push_back(new CWorldSprite("Floor.png", SVector3D<float>(xAxis, yAxis, G_SPRITE_LAYER_Z_POS[ESpriteLayers::Floor])));
				mSpawnPos = { xAxis, yAxis };
			}
		}
	}
}

void CLevel::ReadFileToTileMap(const char* pFilePath)
{
	std::ifstream mapFile;

	mTileMap = new vector<vector<ETileType>*>;

	// Open the file and check if it worked
	mapFile.open(pFilePath);
	if (!mapFile)
	{
		return;
	}

	// Reads the file
	char ch;
	int lineNumber = 1;
	int genratedLines = 0;
	while (mapFile.get(ch))
	{
		// Checks if a vector for a line needs created
		if (lineNumber > genratedLines)
		{
			mTileMap->push_back(new std::vector<ETileType>);
			genratedLines++;
		}

		// Checks if char is valid
		switch (ch)
		{
		case '0':
			mTileMap->at(lineNumber - 1)->push_back(NO_TILE);
			break;

		case '1':
			mTileMap->at(lineNumber - 1)->push_back(WALL);
			break;

		case '2':
			mTileMap->at(lineNumber - 1)->push_back(FLOOR);
			break;

		case '4':
			mTileMap->at(lineNumber - 1)->push_back(WALL_WITH_SIDE);
			break;

		case '5':
			mTileMap->at(lineNumber - 1)->push_back(WALL_WITH_SIDE_FLIPPED_Y);
			break;

		case 'S':
			mTileMap->at(lineNumber - 1)->push_back(SPAWN);
			break;

		case ' ':
			// Blank, do nothing
			break;

		case '\n':
			lineNumber++;
			break;

		default:
			// Char is invalid
			mapFile.close();
			return;
		}
	}

	// Temparly create a new vector;
	vector<vector<ETileType>*>* newTiles = new vector<vector<ETileType>*>;
	for (int i = mTileMap->size() - 1; i >= 0; i--)
	{
		newTiles->push_back(mTileMap->at(i));
	}

	mTileMap = newTiles;

	// Close file
	mapFile.close();
}

// Cleans up the level
void CLevel::ClearLevel()
{

}