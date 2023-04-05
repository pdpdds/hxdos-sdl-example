#include "stdafx.h"
#include "SDL.h"
#include "SDL_image.h"
//#include "SDL_ttf.h"
#include <string>

#include "Board.h"
#include "BoardView.h"
#include "BoardControl.h"


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	bool quit = false;
	Board b;
	BoardView V(&b);
	BoardControl C(&b);

	if (V.BoardViewInit())
	{
		return 1;
	}

	bool NeedUpdate = false;
	player player = X_PLAYER;

	while (quit == false)
	{
		quit = C.CheckControlEvents(player, NeedUpdate);


		if (V.UpdateView(NeedUpdate))
		{
			return 1;
		}
	}

	return 0;

}

