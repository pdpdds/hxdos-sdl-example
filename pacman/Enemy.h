#pragma once

#include <SDL.h>

class Enemy
{
public:
	Enemy();
	~Enemy();
	void Init();
	void Update();
	

	void Draw(SDL_Surface* screen);
public:
	int posX;
	int posY;
	int speed;                // player speed
	bool isAlive;
	SDL_Rect bound;        // bounding box used for collision
	SDL_Rect source;       // rect on sprite sheet
	SDL_Rect topR, bottomR, leftR, rightR;          // top, bottom, left, right rectangle (sides of player)
	enum direction { left, right, up, down, stop };

	bool dir[4];
	direction pDir;                                 // player default direction

	SDL_Rect rectTop;
	SDL_Rect rectLeft;
	SDL_Rect rectBtm;
	SDL_Rect rectRight;

	SDL_Rect spawnPoint;						// reset position when enemy eaten by paci 
	SDL_Rect lowPower;
	                           

private:
	void updateBoundBoxes();
	void generateRandomMove();
	int turnAvalible();
};

