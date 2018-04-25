#pragma once
#include "BUILD_ORDER.h"

using namespace tle;
// Core file
// This holds data core to the game that needs to be passed arround

// players
class CGUI;
class CBullet;
class CPlayer;
class CEProjectile;
class CLevel;
class CTestEnemy;
class CWorldSprite;
class CButton;
class CPowerUp;
enum EPlayers { PlayerTeam, EnemyTeam, NumOfEPlayers };
enum EFontTypes { Large, Medium, NumOfFontTypes };
enum EBackgroundMusic { MainMenuMusic, PlayingMusic, GameOverMusic, NumOfBackgroundMusic };

// game states
enum EGameState { MainMenu, Playing, Paused, GameOver };

// global sprite layers floats
enum ESpriteLayers { Floor, Enemy, Player, UI, NumOfESpriteLayers };
const float G_SPRITE_LAYER_Z_POS[ESpriteLayers::NumOfESpriteLayers] = { 0.1f, 0.03f, 0.02f, 0.01f };

class CCore
{
private:
	// Here will be the instance stored.
	static CCore* pInstance;

	// Stored data
	I3DEngine* pTLEngine;	// pointer to the tl engine
	CInput* pInput;			// pointer to the object that will handle input
	ICamera* pCamera;		// pointer to the game camera
	float mFrameTime;		// time between each frame
	CPlayer* pPlayer[EPlayers::NumOfEPlayers];		// holds pointers to the players - possiable 2 player
	CLevel* pLevel;			// A pointer to the games level
	vector<CBullet*> pActiveBullets;	// vector of pointers to all bullets
	vector<CTestEnemy*> mEnemyList;		// holds a list of enemies
	EGameState mGameState;	// the current game state
	unsigned int mGameScore;// the current score of the game
	CGUI* pGUI;				// pointer to the GUI
	bool mFrontEndBypassed = false;
	bool mFirstRun = true;

	IFont* pText[EFontTypes::NumOfFontTypes];			// pointer to font to write to screen
	const int mTEXT_SIZE[EFontTypes::NumOfFontTypes] = { 150, 50 };
	const int mTEXT_SPACING[EFontTypes::NumOfFontTypes] = { 150, 50 };

	// Main menu elements
	CWorldSprite* pBackgroundSprite;
	CButton* pPlayButton;

	// Skybox
	tle::IMesh* mpSkyBoxMesh;
	tle::IModel* mpSkyboxModel;

	// music
	CAudio* mGameMusic[EBackgroundMusic::NumOfBackgroundMusic];	// array of game music

	// keybinding
	EKeyCode G_EXIT = Key_Escape;

	// Private constructor to prevent instancing.
	CCore();

	void LoadSound();
	void FreeSound();

public:
	//Static access method.
	static CCore* GetInstance();
	vector<CEProjectile*> eBullets;
	vector<CPowerUp*> pPowerUps;	// list of power ups active
  
	// Public functions
	virtual ~CCore();
	void UpdateCore();

	// For changing the scene of the game
	void LoadLevel(const char* levelName = "Levels\\Level1");
	void UnloadGame();
	void SetupMenu();
	void UnloadMenu();
	void FlashLoadScreen();
	void BypassFrontEnd(const char* filePath);

	// Getters
	inline I3DEngine* GetTLEngine() { return pTLEngine; };
	inline CInput* GetInput() { return pInput; };
	inline ICamera* GetCamera() { return pCamera; };
	inline float* GetFrameTimer() { return &mFrameTime; };
	inline CPlayer* GetPlayer(EPlayers player) { return pPlayer[player]; };
	inline CLevel* GetLevel() { return pLevel; };
	inline vector<CTestEnemy*> GetEnemyList() { return mEnemyList; };
	inline vector<CBullet*>* GetBullets() { return &pActiveBullets; };
	inline CGUI* GetGUI() { return pGUI; }
	inline bool GetFirstRun() { return mFirstRun; };

	// Setters
	void AddPlayer(EPlayers player, CPlayer &givenPlayer);
	void AddBullet(CBullet &givenBullet);
	void RemoveBullet(CBullet &givenBullet);
	void AddEnemy(CTestEnemy &givenEnemy);
	void RemoveEnemy(CTestEnemy &givenEnemy);
	void SetGameState(EGameState newState);

	inline void AddScore(int points) { mGameScore += points; };
};