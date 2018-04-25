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
	int yPos = -1;
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
		case '{':
			{ // Signals the start of somthing
				mapFile.get(ch);
				if (ch == 'M')
				{
					mapFile.get(ch);
				}
				else
				{
					// Close file and return
					mapFile.close();
					return mapData;
				}
			}
			break;

		default:
			// The char is invalid or somthing has gone seriusly wrong
			mapData.mMapDataValid = false;
			return mapData;
			break;
		}
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

	// Write start of map positions signal
	mapFile << "{M}" << "\n";
	// Write map positions
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

	// Write start of rooms signal
	mapFile << "{R}" << "\n";
	for (int i = 0; i < pMapData->mRoomData.size(); i++)
	{
		SRoomData* currentRoom = &pMapData->mRoomData[i];

		// Min position of room
		mapFile << "<" << i << "|1|" << currentRoom->mMinPos.x << "|" << currentRoom->mMinPos.y << ">";
		mapFile << " ";

		// Max position of room
		mapFile << "<" << i << "|2|" << currentRoom->mMaxPos.x << "|" << currentRoom->mMaxPos.y << ">";
		mapFile << " ";

		// Door positions in room
		for (int j = 0; j < currentRoom->mDoorPositions.size(); j++)
		{
			mapFile << "<" << i << "|3|" << currentRoom->mDoorPositions[j].x << "|" << currentRoom->mDoorPositions[j].y << ">";
			mapFile << " ";
		}
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