#include "Block.h"

#include "GameManager.h"
Block::Block()
{
	//ctor
	SDL_Rect tmp;
	tmp.x = 1651;
	tmp.y = 33;
	tmp.w = 32;
	tmp.h = 32;

	source = tmp;

	isActive = false;
	id = 0;
}

Block::~Block()
{
	//dtor
}

void Block::Draw(SDL_Surface* screen)
{
	Uint32 color2 = SDL_MapRGB(screen->format, 123, 9, 55);
	Uint32 color = SDL_MapRGB(screen->format, 2, 219, 55);
	if (isActive)
	{
		// Draw block here
		if (id == GameManager::getInstance()->food)
			SDL_FillRect(screen, &destination, color2);
		else if (id == GameManager::getInstance()->power)
			SDL_FillRect(screen, &destination, color);
		else
		{
			SDL_BlitSurface(GameManager::getInstance()->spriteSheet, &source, screen, &destination);
		}
	}
}
