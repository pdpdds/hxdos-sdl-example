#include "Enemy.h"
#include"GameManager.h"
#include <cstdlib>


Enemy::Enemy()
{
	isAlive = false;
	pDir = left;                                 // player default direction
}


Enemy::~Enemy()
{
}


void Enemy::Init()
{
	bound.w = 32;
	bound.h = 32;
	speed = 2 + rand() % 3;
	pDir = up;
	dir[0] = false;
	dir[1] = false;
	dir[2] = false;
	dir[3] = false;


	SDL_Rect tmp;
	tmp.x = 1587;
	tmp.y = 33;
	tmp.w = 32;
	tmp.h = 32;
	
	lowPower = tmp;
}

int Enemy::turnAvalible()
{
	int deltaTurn = 0;
	if ((!GameManager::getInstance()->_level.IsCollidingWithBlock(bottomR, 2, 2)))
	{
		deltaTurn++;
	}

	if ((!GameManager::getInstance()->_level.IsCollidingWithBlock( rightR, 2, 2)))
	{
		deltaTurn++;
	}

	if ((!GameManager::getInstance()->_level.IsCollidingWithBlock(leftR, 2, 2)))
	{
		deltaTurn++;
	}
	if ((!GameManager::getInstance()->_level.IsCollidingWithBlock( topR, 2, 2)))
	{
		deltaTurn++;
	}

	return deltaTurn;
}

void Enemy::generateRandomMove()
{
	
	
	if (pDir == stop)
	{
		int num = rand() % 4;
		if (num == 0)
		{
			
			// down
			if ((!GameManager::getInstance()->_level.IsCollidingWithBlock(rectBtm, 2, 2)))
			{
				pDir = down;
			}

		}
		else if (num == 1)
		{
			if ((!GameManager::getInstance()->_level.IsCollidingWithBlock(rectTop, 2, 2)))
			{
				pDir = up;
			}
		}
		else if (num == 2)
		{
			if ((!GameManager::getInstance()->_level.IsCollidingWithBlock(rectLeft, 2, 2)))
			{
				pDir = left;
			}
		}
		else if (num == 3)
		{
			if ((!GameManager::getInstance()->_level.IsCollidingWithBlock(rectRight, 2, 2)))
			{
				pDir = right;
			}
		}



	}
}
void Enemy::Update()
{
	int tmpTurns = turnAvalible();
	updateBoundBoxes();
	generateRandomMove();
	switch (pDir)
	{
	case left:
		posX -= speed;
		if (posX <= 0)               // When reached the end of screen where is no wall block pacman appears from opposite side
			posX = 770;
		break;

	case right:
		posX += speed;
		if (posX >= 770)		// When reached the end of screen where is no wall block pacman appears from opposite side
			posX = 20;
		break;


	case up:
		
		posY -= speed;
		if (posY <= 0)			// When reached the end of screen where is no wall block pacman appears from opposite side
			posY = 577;
		break;

	case down:
		
		posY += speed;
		if (posY >= 577)	// When reached the end of screen where is no wall block pacman appears from opposite side
			posY = 0;
		break;

	}


	if (GameManager::getInstance()->_level.IsCollidingWithBlock(topR, 2, 2))
	{
		if (pDir == up)
		pDir = stop;
	}
	else if(GameManager::getInstance()->_level.IsCollidingWithBlock(bottomR, 2, 2))
	{
		if (pDir == down)
		pDir = stop;
	}

	if (GameManager::getInstance()->_level.IsCollidingWithBlock(leftR, 2, 2))
	{
		if (pDir == left)
		pDir = stop;
	}
	else if (GameManager::getInstance()->_level.IsCollidingWithBlock(rightR, 2, 2))
	{
		if (pDir == right)
		pDir = stop;
	}

	

	int deltaTurns = turnAvalible();

	if (deltaTurns != tmpTurns)
		pDir = stop;

}

void Enemy::Draw(SDL_Surface* screen)
{
	

	if (isAlive)
	{
		if (!GameManager::getInstance()->powerUp)
			SDL_BlitSurface(GameManager::getInstance()->spriteSheet, &source, screen, &bound);
		else
			SDL_BlitSurface(GameManager::getInstance()->spriteSheet, &lowPower, screen, &bound);
	}
	    
}


void Enemy::updateBoundBoxes()
{

	bound.x = posX;
	bound.y = posY;

	topR.x = bound.x + 5;
	topR.y = bound.y;
	topR.w = bound.w - 10;
	topR.h = 10;


	bottomR.x = bound.x + 5;
	bottomR.y = bound.y + bound.h - 10;
	bottomR.w = bound.w - 10;
	bottomR.h = 10;


	leftR.x = bound.x;
	leftR.y = bound.y + 5;
	leftR.w = 10;
	leftR.h = 22;


	rightR.x = bound.x + bound.w - 10;
	rightR.y = bound.y + 5;
	rightR.w = 10;
	rightR.h = 22;


	// here update 
	rectTop = topR;
	rectLeft = leftR;
	rectBtm = bottomR;
	rectRight = rightR;

	rectLeft.w = leftR.w - 5;
	rectRight.w = rightR.w - 5;

	rectTop.y = topR.y - 10;
	rectBtm.y = bottomR.y + 10;
	rectLeft.x = leftR.x - 5;
	rectRight.x = rightR.x + 10;
}