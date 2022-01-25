#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
//#include "GameManager.h"

class Player
{
public:
	Player();
	~Player();
	void Init();
	void Update();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void stopPlayer();

	void Draw(SDL_Surface* screen);
public:
	int posX;
	int posY;
	int speed;                // player speed
	bool isAlive;
	SDL_Rect bound;        // bounding box used for collision
	SDL_Rect source;       // rect on sprite sheet
	SDL_Rect topR, bottomR, leftR, rightR;          // top, bottom, left, right rectangle (sides of player)
	enum direction {left,right,up,down,stop};

	bool dir[4];
	direction pDir;                                 // player default direction

	SDL_Rect rectTop;
	SDL_Rect rectLeft;
	SDL_Rect rectBtm;
	SDL_Rect rectRight;

	SDL_Rect spawnPoint;						// reset position when enemy eat paci
	int totalLives;

	SDL_Rect frames[13];		// here store all animation frames [index 0 contains stop image, (1,2,3) -> up , 4,5,6 r, 7,8,9 L, 10,11,12 D  ]


private:
	void updateBoundBoxes();
	
	// animation indexes
	int stopAnim;
	int upAnim;
	int rightAnim;
	int leftAnim;
	int downAnim;
	int index;

	float timer;
	
	float animationSpeed;        // incresing this slow down the animation
};

#endif // PLAYER_H
