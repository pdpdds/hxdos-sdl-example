#ifndef LEVEL_H
#define LEVEL_H

#include<fstream>

#include "Block.h"


using namespace std;

class Level
{
public:
	Block _level[19][25];           // contains blocks

public:
	Level();
	~Level();

	bool LoadLevel(char* fileName);
	bool LoadPathMap(char* fileName);
	void PopulateBlocks();                   // using data array we set type and position of blocks
	void DrawLevel(SDL_Surface* screen);
	bool IsCollidingWithBlock(SDL_Rect bound, int precsionX, int presionY);

	bool EatFoodBlock( int id, SDL_Rect bound, int precsionX, int presionY);

private:
	bool Intersect(SDL_Rect r1, SDL_Rect r2);
	int data[19][25];         // store map
	int dataP[19][25];         // store map
};

#endif // LEVEL_H
