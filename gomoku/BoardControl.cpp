#include "BoardControl.h"
#include "BoardView.h"


//The headers
#include "SDL.h"
#include "SDL_image.h"
//#include "SDL_ttf.h"
#include <string>

//The event structure that will be used
SDL_Event event;

bool BoardControl::mouse_events(player& player)
{
	//The mouse offsets
	int x = 0, y = 0;

	bool result = false;

	//If a mouse button was pressed
	if( event.type == SDL_MOUSEBUTTONDOWN )
	{
		//If the left mouse button was pressed
		if( event.button.button == SDL_BUTTON_LEFT )
		{
			//Get the mouse offsets
			x = event.button.x;
			y = event.button.y;
			
			
			
			int x_begin = ( SCREEN_WIDTH - board_->w ) / 2;
			int y_begin = ( SCREEN_HEIGHT - board_->h ) / 2;
			

			//If the mouse is over the button
			if( ( x > x_begin ) && ( x < x_begin + board_->w  ) && ( y > y_begin ) && ( y < y_begin + board_->h ) )
			{
				//Попали на доск?				
				//Пересчитал?x ???интервал 0..9
				int x_total = ( x - x_begin ) / ( board_->w / FIELD_SIZE );
				int y_total = ( y - y_begin ) / ( board_->h / FIELD_SIZE );

				result = board->makeMove(x_total,y_total, player);

			}
			else
			{
				//Не попали на доск?
			}
		}
	}

	return result;

}


void keys_events()
{
	//If a key was pressed
	if( event.type == SDL_KEYDOWN )
	{
		//Now when we want to check when a key is pressed, we check for event type SDL_KEYDOWN.
		//Set the proper message surface
		switch( event.key.keysym.sym )
		{
		case SDLK_UP: ; break;
		case SDLK_DOWN: ; break;
		case SDLK_LEFT: ; break;
		case SDLK_RIGHT: ; break;
		}
	}	
}

bool BoardControl::CheckControlEvents(player& player, bool& NeedUpdate)
{
	//While there's an event to handle
	if( SDL_PollEvent( &event ) )
	{
		//События мыши
		NeedUpdate = mouse_events(player);

		if (NeedUpdate)
		{

			if (player == X_PLAYER) player = O_PLAYER;
			else player = X_PLAYER;

		}
	}


	//If the user has Xed out the window
	if( event.type == SDL_QUIT )
	{
		//Quit the program
		return true;
	}


	return false;

}
//
//void BoardView::StartGame()
//{
//	/*while (не коне?	// мето?b->isWin()
//	{
//		спросить хо?1 - го игрока;
//		b->MakeMove(...);
//		show();
//
//		if (не коне?
//		{
//		спросить хо?2 - го игрока;
//		b->MakeMove(...);
//		show();
//
//		}
//		}
//
//		написать результа?
//	}*/
//
//	cout << "Game is on!";
//	show();
//
//	// the main cycle of game
//	while (board->isWin() == NO_WIN)
//	{
//		bool testFail1 = false;
//		do
//		{
//			int x, y;
//			cout << "Player1 CROSS: input x,y" << endl;
//			cin >> x;
//			cin.ignore(255, '\n');
//
//			cin >> y;
//			cin.ignore(255, '\n');
//
//			testFail1 = board->makeMove(x - 1, y - 1, X_PLAYER);
//			show();
//		} while (!testFail1);
//
//		if (board->isWin() == NO_WIN)
//		{
//			bool testFail2 = false;
//			do
//			{
//				int x, y;
//				cout << "Player2 ZERO: input x,y" << endl;
//				cin >> x;
//				cin.ignore(255, '\n');
//
//				cin >> y;
//				cin.ignore(255, '\n');
//
//				testFail2 = board->makeMove(x - 1, y - 1, O_PLAYER);
//				show();
//			} while (!testFail2);
//		}
//	} // end of while
//
//	// shows result of game
//	if (board->isWin() == X_WIN)
//	{
//		cout << "Player 1 CROSS win!!!" << endl;
//	}
//	else if (board->isWin() == O_WIN)
//	{
//		cout << "Player 2 ZERO win!!!" << endl;
//	}
//	else if (board->isWin() == DRAW)
//	{
//		cout << "Draw!!! Nobody wins :(" << endl;
//	}
//	else
//	{
//
//	}
//
//	system("pause");
//
//}
BoardControl::BoardControl(Board* b)
{
		board = b;
}

BoardControl::~BoardControl()
{

}
