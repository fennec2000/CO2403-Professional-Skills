#pragma once

#define PI 3.14159265f

// TL
#include <TL-Engine.h>

// Standard Libary files
#include <iostream>
#include <vector>
#include <fstream>
#include <windows.h>

// Memory leak detection
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// random
//#include <stdlib.h> // already defined
#include <time.h>

// Other files

// Maths
#include "SVector2D.h"
#include "SVector3D.h"
#include "SMatrix4x4.h"
#include "Maths.h"

// Audio
#include <alut.h>
#include <al.h>
#include "CAudio.h"

// Core systems
#include "CInput.h"
#include "CCore.h"

// Spirte system
#include "NameSettings.h"
#include "ESpriteBlend.h"
#include "SBaseSprite.h"
#include "CUISprite.h"
#include "CWorldSprite.h"
#include "CAnimatedWorldSprite.h"

// Regular UI
#include "SUIData.h"
#include "CHoverUI.h"
#include "CButton.h"

// GUI
#include "CGUI.h"

// Level System
#include "ETileType.h"
#include "ESpawnerTypes.h"
#include "SRoomData.h"
#include "SMapData.h"
#include "CMapIO.h"
#include "CLevel.h"

// Entity
#include "CPowerUp.h"
#include "CPowerShotgun.h"

#include "CBullet.h"
#include "CCharacter.h"
#include "CEnemy.h"
#include "CPlayer.h"
#include "CEProjectile.h"
#include "CTestEnemy.h"
#include "CEnemyShotgun.h"
#include "CEnemyChaingun.h"
