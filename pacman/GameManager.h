#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SDL.h>
//#include <SDL_ttf.h>

#include "Player.h"
#include "Level.h"
#include "Enemy.h"


#include<iostream>
#include<string.h>
#include<sstream>    // used to convert int to char*

class GameManager
{
public:
	GameManager();
	~GameManager();

	static GameManager* getInstance();
	void Init();
	void Draw(SDL_Surface* screen);
	void Update();
	void Dispose();          // release all variables made with new keyword in this method
	bool Intersect(SDL_Rect r1, SDL_Rect r2);
	//void DrawText(SDL_Surface* screen, int x, int y, const char* str, TTF_Font* font);
	//void DrawText(SDL_Surface* screen, int x, int y, int data, TTF_Font* font);


public:
	SDL_Surface* spriteSheet;           // this image contains all sprites
	SDL_Surface* textSurface;
//	TTF_Font * font;					// small font 
//	TTF_Font * font2;					// large font

	bool running;
	int blockWidth;
	int blockHeight;

	// here declare Each game object
	Player pacMan;
	Enemy ghost[4];
	Level _level;


	bool powerUp;					// when true ghosts becomes blue
	int previousIndex;

	int totalFood;
	//blocks types
	int none;
	int solid;
	int player;// later add more types
	int ghostR;   // red ghost
	int power;
	int food;
	int ghostB;
	int ghostP;
	int ghostG;
	
	
private:
	void ResetLevel();
	enum State { mainMenu, play, gameover, winScreen };
	State GameState;
	void OnPlayScreen();
	void OnMainMenu();
	void OnWinScreen();
	void OnGameOver();

	int powerUpTime;    // used when player is power up       
	float timer;


	SDL_Rect playBtnBound;
};

#endif // GAMEMANAGER_H
