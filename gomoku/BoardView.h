#pragma once
#include "Board.h"
#include "SDL.h"
#include "SDL_image.h"
//#include "SDL_ttf.h"
#include <string>

extern SDL_Surface *board_;

//The attributes of the screen
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;



class BoardView
{
private:
	Board* board;
	void show();		
public:
	BoardView( Board* b);
	bool BoardViewInit();
	bool UpdateView(bool& NeedUpdate);
	~BoardView();

	void StartGame();
};

