//==============================================================================
// SDL Tutorial 1
//==============================================================================
#ifndef _CAPP_H_
#define _CAPP_H_

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "mywindow.h"
#include "CPlayer.h"
#include "CPlatform.h"
#include "CEnemy.h"
#include "CSpriteSheet.h"
#include "CMap.h"

#define TICK_INTERVAL    10
#define NUM_ENEMIES     15
#define MAX_SPEED       5
#define MIN_SPEED       2


//==============================================================================
class CApp
{
private:
	enum GAME_STATE {
		START,
		GAME,
		GAME_OVER,
		WIN
	};
	bool Running;
	Uint32 next_time;

	SDL_Window *window;
	SDL_Renderer *renderer;

	Enemy enemies[NUM_ENEMIES];
	CPlayer player;

	//Font
	TTF_Font * font;			    //font object we will use for the message
	SDL_Color color;			    //color of the message
	char message[100];			    //the message string
	SDL_Surface * messageSurface;	//surface that stores the message
	SDL_Texture * messageTexture;	//surface is converted to a texture
	SDL_Rect messageRect;           //location of the message

	int currentTick = 1;
	int tickRange = 100;

	int meters = 0;
	int lives = 5;
	int imortalTime = 1;
	bool isImortal = false;
	CGameObject heart;

	CGameObject gameOver;

	Mix_Music *music = NULL;

	//background
	CGameObject backgroundRight;
	CGameObject backgroundLeft;
	CGameObject layerBack;
	CGameObject layerCosmetic;

	CGameObject gameTitle;
	CGameObject win;

	//
	Platform basePlatform;
	Platform lowerPlatform;
	Platform higherPlatform;
	Platform bridge;

	Platform caves[10];
	int numCaves = 2;
	int caveSpaceDiference;
	Platform cave;

	Platform movingPlatforms[20];
	int numPlatform = 3;
	int platformSpaceDiference;

	Enemy arrows[10];
	int arrowPerRow = 2;
	int arrowSpaceDiference;

	bool touchedBridge = false;
	bool bridgeIsMoved = false;
	//
	GAME_STATE currentStatus = START;
	void Move();
	void CollisionDetect();
	void Draw();
	int currentLevel = 5;
	void nextLevel();
	void initialDraw();
	void loseLife();



public:
	CApp();
	Uint32 time_left(void);
	int OnExecute();
	int gameSpeed = 1;
public:
	bool OnInit();
	void OnEvent(SDL_Event* Event);
	void OnLoop();
	void displayGameStats(int x, int y, char* formattedString, int number);
	void OnRender();
	int LoadSprite(char *file, SDL_Texture **psprite, SDL_Rect *prect);
	void MoveSprites();
	void restartGame();
	void OnCleanup();
};

//==============================================================================

#endif
