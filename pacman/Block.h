#ifndef BLOCK_H
#define BLOCK_H

#include <SDL.h>


class Block
{
	// public variables
public:
	bool isActive;
	SDL_Rect source;                         // used to draw part of sprite
	SDL_Rect destination;                    // used to output block on specific location and collision detection
	int id;
	// public methods
public:
	Block();
	~Block();

	void Draw(SDL_Surface* screen);
};

#endif // BLOCK_H
