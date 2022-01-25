#include "Player.h"
#include "GameManager.h"
Player::Player()
{
	//ctor
	stopAnim = 0;
	upAnim = 1;
	rightAnim = 4;
	leftAnim = 7;
	downAnim = 10;
	index = 0;

	timer = 0.0f;
	
	animationSpeed = 1.0f;        // incresing this slow down the animation
	isAlive = false;
	pDir = left;
	totalLives = 3;

}

Player::~Player()
{
	//dtor
}


void Player::Init()
{
	totalLives = 3;
	bound.w = 32;
	bound.h = 32;
	speed = 2;
	pDir = stop;
	dir[0] = false;
	dir[1] = false;
	dir[2] = false;
	dir[3] = false;

	frames[0].x = 1585;  //stop image bound
	frames[0].y = 63;
	frames[0].w = 32;
	frames[0].h = 32;


	frames[1].x = 1585; // up 1
	frames[1].y = 124;
	frames[1].w = 32;
	frames[1].h = 32;

	frames[2].x = 1616;  // up2
	frames[2].y = 124;
	frames[2].w = 32;
	frames[2].h = 32;

	frames[3].x = 1641;   // up3
	frames[3].y = 124;
	frames[3].w = 32;
	frames[3].h = 32;


	frames[4].x = 1585;    // right 1
	frames[4].y = 95;
	frames[4].w = 32;
	frames[4].h = 32;

	frames[5].x = 1611;    // right 2
	frames[5].y = 95;
	frames[5].w = 32;
	frames[5].h = 32;

	frames[6].x = 1639;    // right 3
	frames[6].y = 95;
	frames[6].w = 32;
	frames[6].h = 32;



	frames[7].x = 1585;    // left 1
	frames[7].y = 153;
	frames[7].w = 32;
	frames[7].h = 32;

	frames[8].x = 1613;    // left 2
	frames[8].y = 153;
	frames[8].w = 32;
	frames[8].h = 32;

	frames[9].x = 1641;    // left 3
	frames[9].y = 153;
	frames[9].w = 32;
	frames[9].h = 32;

	frames[10].x = 1585;    // down 1
	frames[10].y = 183;
	frames[10].w = 32;
	frames[10].h = 32;


	frames[11].x = 1614;    // down 2
	frames[11].y = 183;
	frames[11].w = 32;
	frames[11].h = 32;


	frames[12].x = 1643;    // down 3
	frames[12].y = 183;
	frames[12].w = 32;
	frames[12].h = 32;


}


void Player::Update()
{
	
	switch (pDir)
	{
	case left:
		if (!GameManager::getInstance()->_level.IsCollidingWithBlock( leftR, 2, 2))
		{
			if (posX == 0)               // When reached the end of screen where is no wall block pacman appears from opposite side
				posX = 770;
			else
			{
				dir[1] = true;
				dir[0] = true;
				posX -= speed;			// When Wall posX - 1 to make the codition IsCollidingWithBlock(..) false 
			}        
		}
		else
		{
			dir[0] = false;
			if (dir[1] == false)
				posX++;                     //  No Wall
		}
		break;

	case right:
		if (!GameManager::getInstance()->_level.IsCollidingWithBlock( rightR, 2, 2))
		{
			if (posX == 770)		// When reached the end of screen where is no wall block pacman appears from opposite side
				posX = 20;
			else
			{
				dir[0] = true;

				dir[1] = true;
				posX += speed;
			}
		}
		else
		{
			dir[1] = false;
			if (dir[0] == false)
				posX--;				    //  No Wall
		}break;


	case up:
		if (!GameManager::getInstance()->_level.IsCollidingWithBlock( topR, 2, 2))
		{
			if (posY == 0)			// When reached the end of screen where is no wall block pacman appears from opposite side
				posY = 577;
			else
			{
				dir[3] = true;
				dir[2] = true;
				posY -= speed;
			}
		}
		else
		{
			dir[2] = false;
			if (dir[3] == false)
				posY++;
		}				    //  No Wall
		break;

	case down:
		if (!GameManager::getInstance()->_level.IsCollidingWithBlock( bottomR, 2, 2))
		{
			if (posY == 577)	// When reached the end of screen where is no wall block pacman appears from opposite side
				posY = 0;
			else
			{
				dir[2] = true;
				dir[3] = true;
				posY += speed;
			}
		}
		else
		{
			dir[3] = false;
			if (dir[2] == false)
				posY--;
		}				    //  No Wall
		break;

	}

	updateBoundBoxes();

	if (GameManager::getInstance()->_level.EatFoodBlock(GameManager::getInstance()->food, bound, 2, 2))
	{
		// increment score and decrement total food
		GameManager::getInstance()->totalFood--;

	}
   
	else if (GameManager::getInstance()->_level.EatFoodBlock(GameManager::getInstance()->power, bound, 2, 2))
	{
		// increment score and decrement total food
		GameManager::getInstance()->powerUp = true;

	}

}

void Player::Draw(SDL_Surface* screen)
{
	// here update animation

	timer += 0.5f;

	
	if (timer > animationSpeed)
	{
		timer = 0.0f;
		index++;
	}

	switch (pDir)
	{
	case Player::left:

	    
		if (index > leftAnim + 2)
			index = leftAnim;

		break;
	case Player::right:


	   
		if (index > rightAnim + 2)
			index = rightAnim;

		break;
	case Player::up:


	   
		if (index > upAnim + 2)
			index = upAnim;

		break;
	case Player::down:


	   
		if (index > downAnim + 2)
			index = downAnim;

		break;
	case Player::stop:
		index = 0;
		break;
	}



	 if(isAlive)
	     SDL_BlitSurface(GameManager::getInstance()->spriteSheet,&frames[index],screen,&bound);
}


void Player::stopPlayer()
{
	pDir = stop;

	
}
void Player::moveUp()
{
	pDir = up;
	index = upAnim;
}
void Player::moveDown()
{
	pDir = down;
	index = downAnim;
}
void Player::moveLeft()
{
	pDir = left;
	index = leftAnim;
}
void Player::moveRight()
{
	pDir = right;
	index = rightAnim;
}
void Player::updateBoundBoxes()
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

		rectTop.y = topR.y - 10;
		rectBtm.y = bottomR.y + 10;
		rectLeft.x = leftR.x - 10;
		rectRight.x = rightR.x + 10;

}
