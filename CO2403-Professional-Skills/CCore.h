#pragma once
#include "BUILD_ORDER.h"

using namespace tle;
// Core file
// This holds data core to the game that needs to be passed arround

class CPlayer;
class CLevel;

enum EPlayers { Player1, Player2, NumOfEPlayers };

class CCore
{
private:
	// Here will be the instance stored.
	static CCore* mInstance;

	// Stored data
	I3DEngine* mTLEngine;	// pointer to the tl engine
	float mFrameTime;		// time between each frame
	CPlayer* mpPlayer[EPlayers::NumOfEPlayers];		// holds pointers to the players - possiable 2 player
	CLevel* mpLevel; // A pointer to the games level
	// vector<enemies>		// holds a list of enemies

	// Private constructor to prevent instancing.
	CCore();

public:
	//Static access method.
	static CCore* GetInstance();

	// Public function
	void UpdateCore();

	// Getters
	I3DEngine* GetTLEngine() { return mTLEngine; };
	float* GetFrameTimer() { return &mFrameTime; };
	CPlayer* GetPlayer(EPlayers player) { return mpPlayer[player]; };
	CLevel* GetLevel() { return mpLevel; };

	// Setters
	void AddPlayer(EPlayers player, CPlayer &givenPlayer);
};