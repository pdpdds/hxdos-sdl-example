#include "GameManager.h"
using namespace std;

GameManager::GameManager()
{
	//ctor
	running = true;
	blockWidth = 32;
	blockHeight = 32;

	powerUp = false;					// when true ghosts becomes blue
	previousIndex = -1;

	totalFood = 0;
	//blocks types
	none = 0;
	solid = 1;
	player = 2;// later add more types
	ghostR = 3;   // red ghost
	power = 4;
	food = 5;
	ghostB = 6;
	ghostP = 7;
	ghostG = 8;
	
	GameState = mainMenu;
	
	powerUpTime = 5;    // used when player is power up       
	timer = 0.0f;


	
}

GameManager::~GameManager()
{
	//dtor
}


bool GameManager::Intersect(SDL_Rect r1, SDL_Rect r2)
{
	return !(r2.x > (r1.x + r1.w) || (r2.x + r2.w) < r1.x || r2.y > (r1.y + r1.h) || (r2.y + r2.h) < r1.y);
}


/*void GameManager::DrawText(SDL_Surface* screen, int x, int y, const char* str, TTF_Font* font)
{

	SDL_Rect pos;
	pos.x = x;
	pos.y = y;

	SDL_Color fontcolor = { 0xff, 0xff, 0xff, 0 };
	textSurface = TTF_RenderText_Solid(font2, str, fontcolor);
	SDL_BlitSurface(textSurface, NULL, screen, &pos);
}
void GameManager::DrawText(SDL_Surface* screen, int x, int y, int data, TTF_Font* font)
{
	stringstream str;
	str << data;
	string tmp = str.str();
	char* result = (char*)tmp.c_str();

	SDL_Rect pos;
	pos.x = x;
	pos.y = y;


	SDL_Color fontcolor = { 0xff, 0xff, 0xff, 0 };
	textSurface = TTF_RenderText_Solid(font2, result , fontcolor);
	SDL_BlitSurface(textSurface, NULL, screen, &pos);
}*/

void GameManager::Dispose()
{
//	TTF_Quit();
	delete GameManager::getInstance();

}

GameManager* GameManager::getInstance()
{
	static GameManager *instance = new GameManager();

	return instance;
}



void GameManager::Init()
{

//	TTF_Init();
	spriteSheet = SDL_LoadBMP("asserts/sprite.bmp");

	

	if (spriteSheet == NULL)
		exit(1);
//	font2 = TTF_OpenFont("asserts/font.ttf", 10);
//	if (font2 == NULL)
	//{
	
	//	exit(1);
//	}
	/* Load font */
	//font = TTF_OpenFont("asserts/font.ttf", 54);
//	if (font == NULL)
//	{
		
	//	exit(1);
//	}

	_level.LoadLevel("asserts/level2.txt");

	//_level.LoadPathMap("asserts/path1.txt");

	_level.PopulateBlocks();
	pacMan.Init();

	for (size_t i = 0; i < 4; i++)
	{
		ghost[i].Init();
	}
	



	playBtnBound.x = 298;
	playBtnBound.y = 356;
	playBtnBound.w = 181;
	playBtnBound.h = 93;

}

void GameManager::ResetLevel()
{
	_level.PopulateBlocks();
	pacMan.Init();

	for (size_t i = 0; i < 4; i++)
	{
		ghost[i].Init();
	}
}
void GameManager::Draw(SDL_Surface* screen)
{
	


	switch (GameState)
	{
	case GameManager::mainMenu:

		SDL_Rect src;
		src.x = 780;
		src.y = 0;
		src.w = 800;
		src.h = 600;

		SDL_Rect dst;
		dst.x = 0;
		dst.y = 0;
		dst.w = 800;
		dst.h = 600;

		SDL_BlitSurface(spriteSheet, &src, screen, &dst);

		break;
	case GameManager::play:
		{
		_level.DrawLevel(screen);
		pacMan.Draw(screen);

		for (size_t i = 0; i < 4; i++)
		{
			ghost[i].Draw(screen);
		}



		// Here Draw lifes and other stuff

//		DrawText(screen, 10, 580, "Food Left : ", font);
	//	DrawText(screen, 100, 580, totalFood, font2);

	//	DrawText(screen, 10, 600, "Lifes Left : ", font);
	//	DrawText(screen, 100, 600, pacMan.totalLives, font2);

		// make variable for score and draw here

		break;
		}
	case GameManager::gameover:

		SDL_Rect src1;
		src1.x = 0;
		src1.y = 0;
		src1.w = 800;
		src1.h = 600;

		SDL_BlitSurface(spriteSheet, &src1, screen, &src1);

//		DrawText(screen, 290, 270, "Press Space Key Go to Main Menu : ", font2);


		break;
	case GameManager::winScreen:

		SDL_Rect src2;
		src2.x = 780;
		src2.y = 0;
		src.w = 800;
		src2.h = 600;

		SDL_Rect dst1;
		dst1.x = 0;
		dst1.y = 0;
		dst1.w = 800;
		dst1.h = 600;

		SDL_BlitSurface(spriteSheet, &src2, screen, &dst1);


		break;

	}

}



void GameManager::OnPlayScreen()
{

	pacMan.Update();

	for (size_t i = 0; i < 4; i++)
	{
		ghost[i].Update();

		// here checks collision between paci vs pinky | inky | and other 2 ghosts
		if (Intersect(ghost[i].bound, pacMan.bound))
		{
			if (powerUp)
			{
				ghost[i].posX = ghost[i].spawnPoint.x;
				ghost[i].posY = ghost[i].spawnPoint.y;
			}
			else
			{
				pacMan.posX = pacMan.spawnPoint.x;
				pacMan.posY = pacMan.spawnPoint.y;
				pacMan.totalLives--;
			}
		}

	}
}


void GameManager::Update()
{

	SDL_Event event;
	 
	if (pacMan.totalLives <= 0)
	{
		GameState = gameover;
		ResetLevel();
	}
		
	if (totalFood <= 0)
	{
		GameState = winScreen;
		
	}

	if (powerUp)
	{
		timer += 0.01;

		if (timer > powerUpTime)
		{
			timer = 0;
			powerUp = false;
		}
	}

	
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			running = false;
			break;


		case SDL_MOUSEBUTTONDOWN:

		{

									if (GameState == gameover || GameState == play)
										break;
									int x = event.button.x;
									int y = event.button.y;

									if (x > playBtnBound.x && x < playBtnBound.x + playBtnBound.w
										&& y > playBtnBound.y && y < playBtnBound.y + playBtnBound.h
										&& event.button.button == SDL_BUTTON_LEFT)
									{
										ResetLevel();
										GameState = play;
									}



		}
			

			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_UP:
				
				
				if (GameState != play)
					break;

				if (!_level.IsCollidingWithBlock( pacMan.rectTop, 2, 2))
				{
					pacMan.moveUp();
				}
				    
				break;
			case SDLK_LEFT:

				if (GameState != play)
					break;
				
				if (!_level.IsCollidingWithBlock( pacMan.rectLeft, 2, 2) )
				{

					pacMan.moveLeft();
				}
				    
				break;
			case SDLK_DOWN:

				
				if (GameState != play)
					break;

				if (!_level.IsCollidingWithBlock(pacMan.rectBtm, 2, 2))
				{
					pacMan.moveDown();
				}
				   

				break;
			case SDLK_RIGHT:

				
				if (GameState != play)
					break;

				if (!_level.IsCollidingWithBlock( pacMan.rectRight, 2, 2))
				{
					pacMan.moveRight();
				}


				break;

			case SDLK_SPACE:
					if (GameState == gameover)
						GameState = mainMenu;
					else if (GameState == mainMenu)
						GameState = play;
					break;
				
			}
			break;
		}


	}



	// here call update methods of game objects


	switch (GameState)
	{
	case GameManager::mainMenu:

		

		break;
	case GameManager::play:
		OnPlayScreen();
		break;
	case GameManager::gameover:

		break;
	case GameManager::winScreen:

		break;
	
	}


}
