
#include <Windows.h>
#include <SDL.h>

#include "GameManager.h"

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
    //===========================================================================//
    //                             INIT CODE HERE
    //===========================================================================//
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface *screen;

#ifdef _DEBUG
	screen = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);
#else
	screen = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE | SDL_FULLSCREEN);
#endif

	const int FPS = 30;
	Uint32 start;

	// create one instance of GameManager
	GameManager* manager =  GameManager::getInstance();
	manager->Init();

	SDL_SetColorKey(manager->spriteSheet, SDL_SRCCOLORKEY, SDL_MapRGB(screen->format, 0xff, 0x00, 0xff));

	Uint32 color = SDL_MapRGB(screen->format, 0x00,0x00,0x00);

	while(manager->running)
    {
		start = SDL_GetTicks();

		//render
		SDL_FillRect(screen,&screen->clip_rect,color);


        // here update
		manager->Update();
		// here Draw
		manager->Draw(screen);


		
        SDL_Flip(screen);
		if(1000/FPS > SDL_GetTicks()-start)
        {
			SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
		}

	}
	manager->Dispose();

	SDL_Quit();
	return 0;
}
