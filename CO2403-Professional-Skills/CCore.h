#pragma once
#include "BUILD_ORDER.h"

using namespace tle;
// Core file
// This holds data core to the game that needs to be passed arround

// players
class CPlayer;
class CEProjectile;
class CLevel;
enum EPlayers { Player1, Player2, NumOfEPlayers };


// game states
enum EGameState { Playing, Paused };

// global sprite layers floats
enum ESpriteLayers { Floor, Enemy, Player, UI, NumOfESpriteLayers };
const float G_SPRITE_LAYER_Z_POS[ESpriteLayers::NumOfESpriteLayers] = { 1.0f, 0.3f, 0.2f, 0.1f };

class CCore
{
private:
	// Here will be the instance stored.
	static CCore* pInstance;

	// Stored data
	I3DEngine* pTLEngine;	// pointer to the tl engine
	ICamera* pCamera;		// pointer to the game camera
	float mFrameTime;		// time between each frame
	CPlayer* pPlayer[EPlayers::NumOfEPlayers];		// holds pointers to the players - possiable 2 player
	CLevel* pLevel; // A pointer to the games level
	// vector<enemies>		// holds a list of enemies
	EGameState mGameState;	// the current game state
	unsigned int mGameScore;// the current score of the game

	// Private constructor to prevent instancing.
	CCore();

public:
	//Static access method.
	static CCore* GetInstance();
	vector<CEProjectile*> eBullets;
  
	// Public functions
	void UpdateCore();

	// Getters
	I3DEngine* GetTLEngine() { return pTLEngine; };
	ICamera* GetCamera() { return pCamera; };
	float* GetFrameTimer() { return &mFrameTime; };
	CPlayer* GetPlayer(EPlayers player) { return pPlayer[player]; };
	CLevel* GetLevel() { return pLevel; };

	// Setters
	void AddPlayer(EPlayers player, CPlayer &givenPlayer);
	void AddBullet(float ex, float ey, float ez);
	void updateBullets();
};