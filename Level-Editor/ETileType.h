// ETileType.h 21-02-2018
// William John Atkin WJAtkin@UCLan.ac.uk

#pragma once
#include "BUILD_ORDER.h"

enum ETileType
{
	NO_TILE = 0,
	WALL = 1,
	FLOOR = 2,
	WALL_WITH_SIDE = 3,
	WALL_WITH_SIDE_FLIPPED_Y = 4,
	WALL_SERVER_ANIMATED = 5,
	DOOR = 6,
	DOOR_ROT = 7,
	DOOR_OPEN = 8,
	DOOR_ROT_OPEN = 9,
	END_GOAL = 10
};
