// CMapIO.h 11-03-2018
// William John Atkin WJAtkin@UCLan.ac.uk
#include "BUILD_ORDER.h"

CMapIO::CMapIO() { }

CMapIO::~CMapIO() { }

SMapData CMapIO::ReadMapFile(const char* pMapFilePath)
{
	SMapData mapData;

	string fullFilePath = pMapFilePath;
	fullFilePath += ".edm";

	// Open the file and check if it worked
	std::ifstream mapFile;
	mapFile.open(fullFilePath);
	if (!mapFile)
	{
		mapData.mMapDataValid = false;
		return mapData;
	}

	// Reads the file
	char ch;
	int xPos = 0;
	int yPos = 0;
	while (mapFile.get(ch))
	{
		switch (ch)
		{
		case '<':
			{
				// This is the start of map data
				string currentData;
				// Gets the tile type
				mapFile.get(ch);
				while (ch != '|')
				{
					currentData += ch;
					mapFile.get(ch);
				}
				// Sets the tile type
				mapData.mTileMap[yPos].at(xPos) = static_cast<ETileType>(stoi(currentData));
				// And the collision type
				mapData.mCollisionMap[yPos].at(xPos) = false;

				// Gets the spawn data
				currentData = "";
				// Gets the tile type
				mapFile.get(ch);
				while (ch != '|')
				{
					currentData += ch;
					mapFile.get(ch);
				}
				// Sets the tile type
				mapData.mSpawnerMap[yPos].at(xPos) = static_cast<ESpawnTypes>(stoi(currentData));

				// Gets the item data
				currentData = "";
				// Gets the tile type
				mapFile.get(ch);
				while (ch != '>')
				{
					currentData += ch;
					mapFile.get(ch);
				}
				// Discard data for now

				// Increement xpos
				xPos++;
			}
			break;

		case ' ':
			// Blank, do nothing
			break;
		
		case '\n':
			yPos++;
			xPos = 0;
			break;

		default:
			// The char is invalid or somthing has gone seriusly wrong
			mapData.mMapDataValid = false;
			return mapData;
			break;
		}

		//// Checks if char is valid
		//switch (ch)
		//{
		//case (char)NO_TILE + 48:
		//	delete levelSprites[xPos]->at(yPos);
		//	levelSprites[xPos]->at(yPos) = nullptr;
		//	break;
		//
		//case (char)WALL + 48:
		//	newTileMap[xPos]->at(yPos) = WALL;
		//	GenerateSprite("FullWall.png", { xPos, yPos });
		//	break;
		//
		//case (char)FLOOR + 48:
		//	newTileMap[xPos]->at(yPos) = FLOOR;
		//	GenerateSprite("Floor.png", { xPos, yPos });
		//	break;
		//
		//case (char)WALL_WITH_SIDE + 48:
		//	newTileMap[xPos]->at(yPos) = WALL_WITH_SIDE;
		//	GenerateSprite("WallSide.png", { xPos, yPos });
		//	break;
		//
		//case (char)WALL_WITH_SIDE_FLIPPED_Y + 48:
		//	newTileMap[xPos]->at(yPos) = WALL_WITH_SIDE_FLIPPED_Y;
		//	GenerateSprite("WallSide.png", { xPos, yPos });
		//	levelSprites[xPos]->at(yPos)->RotateZ(180.0f);
		//	break;
		//
		//case (char)SPAWN + 48:
		//	newTileMap[xPos]->at(yPos) = SPAWN;
		//	GenerateSprite("FloorSpawn.png", { xPos, yPos });
		//	break;

		//if (ch != ' ' && ch != '\n')
		//{
		//	xPos++;
		//}
	}

	// Close file and return
	mapFile.close();
	return mapData;
}

int CMapIO::SaveMapFile(SMapData* pMapData, const char* pMapFilePath)
{
	ofstream mapFile;
	string fullFileName = pMapFilePath;
	fullFileName += ".edm";
	mapFile.open(fullFileName);

	for (int yPos = 0; yPos < CLevel::MAP_MAX_SIZE.y; yPos++)
	{
		for (int xPos = 0; xPos < CLevel::MAP_MAX_SIZE.x; xPos++)
		{
			// Open the start of the data
			string posData = "<";
			// Append the tile data
			posData.append(to_string(pMapData->mTileMap[yPos].at(xPos)));
			// Spacer
			posData += "|";
			// Apped the spawner data
			posData.append(to_string(pMapData->mSpawnerMap[yPos].at(xPos)));
			// Spacer
			posData += "|";
			// Append item data
			posData += "0";
			// End the data
			posData += ">";

			// Add this data to the file
			mapFile << posData << " ";
		}
		// New line
		mapFile << "\n";
	}

	mapFile.close();
	return 0;
}

int CMapIO::EncryptMapFile()
{
	return -1;
}

int CMapIO::DecryptMapFile()
{
	return -1;
}