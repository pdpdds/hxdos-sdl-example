#include "BoardView.h"
#include <iostream>
#include <iomanip>
#include <ctime>

//The headers
#include "SDL.h"
#include "SDL_image.h"
//#include "SDL_ttf.h"
#include <string>

//The surfaces
SDL_Surface *board_ = NULL;
SDL_Surface *background = NULL;
SDL_Surface *message = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *cross = NULL;
SDL_Surface *zero = NULL;



//The font that's going to be used
//TTF_Font *font = NULL;

//The color of the font
SDL_Color textColor = { 255, 255, 255 };


using namespace std;


static SDL_Surface *load_image( std::string filename ) 
{
	//The image that's loaded
	SDL_Surface* loadedImage = NULL;

	//The optimized image that will be used
	SDL_Surface* optimizedImage = NULL;

	//Load the image
	loadedImage = IMG_Load( filename.c_str() );

	//If the image loaded
	if( loadedImage != NULL )
	{
		//Create an optimized image
		optimizedImage = SDL_DisplayFormat( loadedImage );

		//Free the old image
		SDL_FreeSurface( loadedImage );
	}

	//Return the optimized image
	return optimizedImage;
}

static void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
	//Temporary rectangle to hold the offsets
	SDL_Rect offset;

	//Get the offsets
	offset.x = x;
	offset.y = y;

	//Blit the surface
	SDL_BlitSurface( source, NULL, destination, &offset );
}

static bool init()
{
	//Initialize all SDL subsystems
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
	{
		return false;    
	}

	//Set up the screen
	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

	//If there was an error in setting up the screen
	if( screen == NULL )
	{
		return false;    
	}

	//Initialize SDL_ttf
	//if( TTF_Init() == -1 )
//	{
//		return false;    
//	}


	//Set the window caption
	SDL_WM_SetCaption( "SDL_test", NULL );

	//If everything initialized fine
	return true;
}

static bool load_files()
{

	//Load the cross
	cross = load_image( "cross.png" );
	//If there was an error in loading the cross
	if( cross == NULL )
	{
		char* szError = SDL_GetError();
		return false;    
	}

	//Load the cross
	zero = load_image( "zero.png" );
	//If there was an error in loading the cross
	if( zero == NULL )
	{
		return false;    
	}



	//Load the board_
	board_ = load_image( "board.png" );

	//If there was an error in loading the board_
	if( board_ == NULL )
	{
		return false;    
	}

	//Load the background
	background = load_image( "back.png" );
	if ( background == NULL)
	{
		return false;    
	}

	//Open the font
//	font = TTF_OpenFont( "lazy.ttf", 28 );


	//If there was an error in loading the font
//	if( font == NULL )
//	{
//		return false;
//	}


	//If everything loaded fine
	return true;    
}



static void clean_up()
{
	//Free the zero
	SDL_FreeSurface( zero );
	SDL_FreeSurface( cross );
	SDL_FreeSurface( board_ );
	SDL_FreeSurface( message );
	//Close the font that was used
//	TTF_CloseFont( font );


	//Quit SDL_ttf
//	TTF_Quit();

	//Quit SDL
	SDL_Quit();    
}




BoardView::BoardView( Board* b)
{
	board = b;

}

bool BoardView::BoardViewInit()
{
	//Make sure the program waits for a quit
	bool quit = false;

	//Initialize
	if( init() == false )
	{
		return 1;    
	}

	//Load the files
	if( load_files() == false )
	{
		return 1;    
	}

    //Apply the surface to the screen
	apply_surface( 0, 0, background, screen );

	//Apply the message centered on the screen
	apply_surface( ( SCREEN_WIDTH - board_->w ) / 2, ( SCREEN_HEIGHT - board_->h ) / 2, board_, screen );


	//Render the text
//	message = TTF_RenderText_Solid( font, "Let's go...", textColor );

	//If there was an error in rendering the text
//	if( message == NULL )
//	{
//		return 1;    
//	}

	//Apply the surface to the screen
	//apply_surface( ( SCREEN_WIDTH - message->w ) / 2, 10, message, screen );

	//Update the screen
	if( SDL_Flip( screen ) == -1 )
	{
		return 1;    
	}

	return 0;
}


BoardView::~BoardView()
{
	//Очистить ресурс?	clean_up();
}

bool BoardView::UpdateView(bool& NeedUpdate)
{
	//If a message needs to be displayed
	if(NeedUpdate)
	{

		//Apply the background to the screen
		apply_surface( 0, 0, background, screen );
		//Apply the board_ centered on the screen
		apply_surface( ( SCREEN_WIDTH - board_->w ) / 2, ( SCREEN_HEIGHT - board_->h ) / 2, board_, screen );

		//Нарисовать крестики ?нолики
		show();

		if(board->isWin() == NO_WIN)
		{
			//Render the text
//			message = TTF_RenderText_Solid( font, "Let's go...", textColor );
			//Apply the message on the top
		//	apply_surface( ( SCREEN_WIDTH - message->w ) / 2, 10, message, screen );

		}
		if (board->isWin() == X_WIN)
		{
			//Render the text
		//	message = TTF_RenderText_Solid( font, "Player 1 CROSS win!!!", textColor );
			//Apply the message on the top
			//apply_surface( ( SCREEN_WIDTH - message->w ) / 2, 10, message, screen );

	
		}
		else if (board->isWin() == O_WIN)
		{
			//Render the text
		//	message = TTF_RenderText_Solid( font, "Player 2 ZERO win!!!", textColor );
			//Apply the message on the top
			//apply_surface( ( SCREEN_WIDTH - message->w ) / 2, 10, message, screen );
		}
		else if (board->isWin() == DRAW)
		{
			//Render the text
//			message = TTF_RenderText_Solid( font, "Draw!!! Nobody wins :(", textColor );
			//Apply the message on the top
			//apply_surface( ( SCREEN_WIDTH - message->w ) / 2, 10, message, screen );
		}
		else
		{

		}
		//apply_surface( ( ( 1 * (board_->w / Board::FIELD_SIZE) ) + ( SCREEN_WIDTH - board_->w ) / 2 ) + 2, 
		//	( ( 4 * (board_->h / Board::FIELD_SIZE) ) + ( SCREEN_HEIGHT - board_->h ) / 2 ) + 2, 
		//	cross, screen );
	//apply_surface( ( ( 4 * (board_->w / Board::FIELD_SIZE) ) + ( SCREEN_WIDTH - board_->w ) / 2 ) + 2, 
		//	           ( ( 4 * (board_->h / Board::FIELD_SIZE) ) + ( SCREEN_HEIGHT - board_->h ) / 2 ) + 2, 
		//			   cross, screen );

		//SDL_Delay(100);
		//Null the surface pointer
		//message = NULL;
	}

	//Update the screen
	if( SDL_Flip( screen ) == -1 )
	{
		return true;
	}

	return false;
}

void show_cross(int i, int j)
{
	//Apply the message on the top
	//apply_surface( i * (board_->w / Board::FIELD_SIZE), j * (board_->h / Board::FIELD_SIZE), cross, screen );

	apply_surface( ( ( i * (board_->w / FIELD_SIZE) ) + ( SCREEN_WIDTH - board_->w ) / 2 ) + 2, 
		( ( j * (board_->h / FIELD_SIZE) ) + ( SCREEN_HEIGHT - board_->h ) / 2 ) + 2, 
		cross, screen );
}

void show_zero(int i, int j)
{
	//Apply the message on the top
	//apply_surface( i * (board_->w / Board::FIELD_SIZE), j * (board_->h / Board::FIELD_SIZE), zero, screen );

	apply_surface( ( ( i * (board_->w / FIELD_SIZE) ) + ( SCREEN_WIDTH - board_->w ) / 2 ) + 2, 
		( ( j * (board_->h / FIELD_SIZE) ) + ( SCREEN_HEIGHT - board_->h ) / 2 ) + 2, 
		zero, screen );
}


void BoardView::show()
{
	cout << endl;

	cout << "    ";

	for (int k = 0; k < FIELD_SIZE; k++)
	{
		cout << k + 1 << " ";
	}

	cout << endl << "    ";

	for (int m = 0; m < FIELD_SIZE; m++)
	{
		cout << "_ ";
	}

	cout << endl;

	for (int i = 0; i < FIELD_SIZE; i++)
	{
		cout << setw(2) << i + 1 << " " << "|";

		for (int j = 0; j < FIELD_SIZE; j++)
		{
			//выво?клетки i,j (b->getCell())

			int Cell = board->getCell(i, j);
			if (Cell == X)
			{
				//cout << "X" << "|";
				//Нарисовать крес??клетке
				show_cross(i,j);

			}
			else if (Cell == O)
			{
				//cout << "O" << "|";
				//Нарисовать ноль ?клетке
				show_zero(i,j);
			}
			else if (Cell == NUL)
			{
				//cout << "_" << "|";
				//Ничего не рисовать
			}
			else { }

			if (j == (FIELD_SIZE - 1)) cout << endl;
		}
	}

	cout << endl;
}


void BoardView::StartGame()
{
	/*while (не коне?	// мето?b->isWin()
	{
		спросить хо?1 - го игрока;
		b->MakeMove(...);
		show();

		if (не коне?
		{
		спросить хо?2 - го игрока;
		b->MakeMove(...);
		show();

		}
		}

		написать результа?
	}*/

	cout << "Game is on!";
	show();

	// the main cycle of game
	while (board->isWin() == NO_WIN)
	{
		bool testFail1 = false;
		do
		{
			int x, y;
			cout << "Player1 CROSS: input x,y" << endl;
			cin >> x;
			cin.ignore(255, '\n');

			cin >> y;
			cin.ignore(255, '\n');

			testFail1 = board->makeMove(x - 1, y - 1, X_PLAYER);
			show();
		} while (!testFail1);

		if (board->isWin() == NO_WIN)
		{
			bool testFail2 = false;
			do
			{
				int x, y;
				cout << "Player2 ZERO: input x,y" << endl;
				cin >> x;
				cin.ignore(255, '\n');

				cin >> y;
				cin.ignore(255, '\n');

				testFail2 = board->makeMove(x - 1, y - 1, O_PLAYER);
				show();
			} while (!testFail2);
		}
	} // end of while

	// shows result of game
	if(board->isWin() == NO_WIN)
	{
		
	}
	if (board->isWin() == X_WIN)
	{
		cout << "Player 1 CROSS win!!!" << endl;
	}
	else if (board->isWin() == O_WIN)
	{
		cout << "Player 2 ZERO win!!!" << endl;
	}
	else if (board->isWin() == DRAW)
	{
		cout << "Draw!!! Nobody wins :(" << endl;
	}
	else
	{

	}

	system("pause");

}

//void BoardView::TestGame()
//{
//	cout << "Game is test!";
//	show();
//
//	srand(time(0));
//
//	// the main cycle of game
//	while (board->isWin() == NO_WIN)
//	{
//		bool testFail1 = false;
//		do
//		{
//			int x, y;
//			cout << "Player1 CROSS: input x,y" << endl;
//			x = rand() % 10 + 1;
//			cout << x << endl;
//
//			y = rand() % 10 + 1;
//			cout << y;
//
//			testFail1 = board->makeMove(x - 1, y - 1, X_PLAYER);
//			show();
//		} while (!testFail1);
//
//		
//		if (board->isWin() == NO_WIN)
//		{
//			bool testFail2 = false;
//			do
//			{
//				int x, y;
//				cout << "Player2 ZERO: input x,y" << endl;
//				x = rand() % 10 + 1;
//				cout << x << endl;
//
//				y = rand() % 10 + 1;
//				cout << y;
//
//				testFail2 = board->makeMove(x - 1, y - 1, O_PLAYER);
//				show();
//			} while (!testFail2);
//		}
//	}  // end of while
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
//}