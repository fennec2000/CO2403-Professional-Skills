// CMapIO.h 11-03-2018
// William John Atkin WJAtkin@UCLan.ac.uk
#include "BUILD_ORDER.h"
#pragma once

class CMapIO
{
public:
	// IO
	static SMapData ReadMapFile(const char* pMapFilePath);
	static int SaveMapFile(SMapData* pMapData, const char* pMapFilePath);

private:
	CMapIO();
	~CMapIO();

	// Encryption
	static int EncryptMapFile();
	static int DecryptMapFile();
};

