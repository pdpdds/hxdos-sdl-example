#include "Level.h"
#include "GameManager.h"

Level::Level()
{
	//ctor
}

Level::~Level()
{
	//dtor
}

//
//bool Level::LoadPathMap(char* fileName)
//{
//	bool valid = false;
//	ifstream file(fileName);
//	int i, j;
//	i = j = 0;
//	int dat;
//
//	if (file.is_open())
//	{
//		while (true)
//		{
//			file >> dat;
//			std::cout << "read : " << dat;
//			if (dat + '0' == '\n')
//				continue;
//
//			if (dat + '0' == '#')
//				break;
//
//			if (dat + '0' == ',')
//			{
//				j++;
//				continue;
//			}
//			else if (dat + '0' == '-')
//			{
//				j = 0;
//				i++;
//				continue;
//			}
//
//			dataP[i][j] = dat ;
//
//		}
//
//
//		valid = true;
//		file.close();
//
//	}
//
//	return valid;
//}


bool Level::LoadLevel(char* fileName)
{
	bool valid = false;
	ifstream file(fileName);
	int i, j;
	i = j = 0;
	char dat;

	if (file.is_open())
	{
		while (true)
		{
			file >> dat;

			if (dat == '\n')
				continue;

			if (dat == '#')
				break;

			if (dat == ',')
			{
				j++;
				continue;
			}
			else if (dat == '-')
			{
				j = 0;
				i++;
				continue;
			}

			data[i][j] = dat - '0';

		}


		valid = true;
		file.close();

	}

	//// here copy path map
	//for (size_t i = 0; i < 19; i++)
	//{
	//	for (size_t j = 0; j < 25; j++)
	//	{
	//		if (data[i][j] == 0)
	//			dataP[i][j] = 0;
	//		else if (data[i][j] == 1)
	//			dataP[i][j] = -1;
	//	}
	//}



	

	return valid;
}
void Level::PopulateBlocks()
{
	int tGosts = 0;
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			if (data[i][j] == GameManager::getInstance()->none)
			{
				SDL_Rect rect;
				rect.x = j*GameManager::getInstance()->blockWidth;
				rect.y = i*GameManager::getInstance()->blockHeight;
				rect.w = GameManager::getInstance()->blockWidth;
				rect.h = GameManager::getInstance()->blockHeight;

				_level[i][j].isActive = false;
				_level[i][j].id = GameManager::getInstance()->none;
				_level[i][j].destination = rect;
				//   _level[i][j].source = here set rect of sprite sheet;

			}
			else if (data[i][j] == GameManager::getInstance()->solid)
			{
				SDL_Rect rect;
				rect.x = j*GameManager::getInstance()->blockWidth;
				rect.y = i*GameManager::getInstance()->blockHeight;
				rect.w = GameManager::getInstance()->blockWidth;
				rect.h = GameManager::getInstance()->blockHeight;

				_level[i][j].isActive = true;
				_level[i][j].id = GameManager::getInstance()->solid;
				_level[i][j].destination = rect;
				//   _level[i][j].source = here set rect of sprite sheet;

			}
			else if (data[i][j] == GameManager::getInstance()->player)
			{
				SDL_Rect rect;
				rect.x = j*GameManager::getInstance()->blockWidth;
				rect.y = i*GameManager::getInstance()->blockHeight;
				rect.w = GameManager::getInstance()->blockWidth ;
				rect.h = GameManager::getInstance()->blockHeight;

				_level[i][j].isActive = false;
				_level[i][j].id = GameManager::getInstance()->none;

				// here set position of player
				GameManager::getInstance()->pacMan.posX = rect.x;
				GameManager::getInstance()->pacMan.posY = rect.y;
				//GameManager::getInstance()->pacMan.bound = rect;
				GameManager::getInstance()->pacMan.isAlive = true;
				GameManager::getInstance()->pacMan.spawnPoint = rect;

			}
			else if (data[i][j] == GameManager::getInstance()->ghostR)
			{
				SDL_Rect rect;
				rect.x = j*GameManager::getInstance()->blockWidth;
				rect.y = i*GameManager::getInstance()->blockHeight;
				rect.w = GameManager::getInstance()->blockWidth;
				rect.h = GameManager::getInstance()->blockHeight;

				_level[i][j].isActive = false;
				_level[i][j].id = GameManager::getInstance()->none;

				// here set position of player
				GameManager::getInstance()->ghost[tGosts].posX = rect.x;
				GameManager::getInstance()->ghost[tGosts].posY = rect.y;
				//GameManager::getInstance()->pacMan.bound = rect;
				GameManager::getInstance()->ghost[tGosts].isAlive = true;
				GameManager::getInstance()->ghost[tGosts].spawnPoint = rect;

				SDL_Rect tmp;
				tmp.x = 1587;
				tmp.y = 1;
				tmp.w = 32;
				tmp.h = 32;
				GameManager::getInstance()->ghost[tGosts].source = tmp;
				tGosts++;

			}
			else if (data[i][j] == GameManager::getInstance()->ghostB)
			{
				SDL_Rect rect;
				rect.x = j*GameManager::getInstance()->blockWidth;
				rect.y = i*GameManager::getInstance()->blockHeight;
				rect.w = GameManager::getInstance()->blockWidth;
				rect.h = GameManager::getInstance()->blockHeight;

				_level[i][j].isActive = false;
				_level[i][j].id = GameManager::getInstance()->none;

				// here set position of player
				GameManager::getInstance()->ghost[tGosts].posX = rect.x;
				GameManager::getInstance()->ghost[tGosts].posY = rect.y;
				//GameManager::getInstance()->pacMan.bound = rect;
				GameManager::getInstance()->ghost[tGosts].isAlive = true;
				GameManager::getInstance()->ghost[tGosts].spawnPoint = rect;
				
				SDL_Rect tmp;
				tmp.x = 1619;
				tmp.y = 1;
				tmp.w = 32;
				tmp.h = 32;
				GameManager::getInstance()->ghost[tGosts].source = tmp;

				
				tGosts++;

			}
			else if (data[i][j] == GameManager::getInstance()->ghostP)
			{
				SDL_Rect rect;
				rect.x = j*GameManager::getInstance()->blockWidth;
				rect.y = i*GameManager::getInstance()->blockHeight;
				rect.w = GameManager::getInstance()->blockWidth;
				rect.h = GameManager::getInstance()->blockHeight;

				_level[i][j].isActive = false;
				_level[i][j].id = GameManager::getInstance()->none;

				// here set position of player
				GameManager::getInstance()->ghost[tGosts].posX = rect.x;
				GameManager::getInstance()->ghost[tGosts].posY = rect.y;
				//GameManager::getInstance()->pacMan.bound = rect;
				GameManager::getInstance()->ghost[tGosts].isAlive = true;
				GameManager::getInstance()->ghost[tGosts].spawnPoint = rect;

				SDL_Rect tmp;
				tmp.x = 1651;
				tmp.y = 1;
				tmp.w = 32;
				tmp.h = 32;
				GameManager::getInstance()->ghost[tGosts].source = tmp;


				tGosts++;

			}
			else if (data[i][j] == GameManager::getInstance()->ghostG)
			{
				SDL_Rect rect;
				rect.x = j*GameManager::getInstance()->blockWidth;
				rect.y = i*GameManager::getInstance()->blockHeight;
				rect.w = GameManager::getInstance()->blockWidth;
				rect.h = GameManager::getInstance()->blockHeight;

				_level[i][j].isActive = false;
				_level[i][j].id = GameManager::getInstance()->none;

				// here set position of player
				GameManager::getInstance()->ghost[tGosts].posX = rect.x;
				GameManager::getInstance()->ghost[tGosts].posY = rect.y;
				//GameManager::getInstance()->pacMan.bound = rect;
				GameManager::getInstance()->ghost[tGosts].isAlive = true;
				GameManager::getInstance()->ghost[tGosts].spawnPoint = rect;
				

				SDL_Rect tmp;
				tmp.x = 1619;
				tmp.y = 33;
				tmp.w = 32;
				tmp.h = 32;
				GameManager::getInstance()->ghost[tGosts].source = tmp;
				
				tGosts++;

			}
			else if (data[i][j] == GameManager::getInstance()->food)
			{
				SDL_Rect rect;
				rect.x = (j*GameManager::getInstance()->blockWidth) + 11;
				rect.y = (i*GameManager::getInstance()->blockHeight) + 11;
				rect.w = 10;
				rect.h = 10;

				_level[i][j].isActive = true;
				_level[i][j].id = GameManager::getInstance()->food;

				_level[i][j].destination = rect;



				GameManager::getInstance()->totalFood++;
			}

			else if (data[i][j] == GameManager::getInstance()->power)
			{
				SDL_Rect rect;
				rect.x = (j*GameManager::getInstance()->blockWidth) + 8;
				rect.y = (i*GameManager::getInstance()->blockHeight) + 8;
				rect.w = 16;
				rect.h = 16;

				_level[i][j].isActive = true;
				_level[i][j].id = GameManager::getInstance()->power;

				_level[i][j].destination = rect;
			}
		}
	}
}
void Level::DrawLevel(SDL_Surface* screen)
{
	Uint32 color2 = SDL_MapRGB(screen->format, 23, 99, 55);
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			// here call Draw Block
//			if (_level[i][j].isActive)
//				SDL_FillRect(screen, &_level[i][j].destination, color2);
			//   SDL_BlitSurface(GameManager::getInstance()->spriteSheet, &_level[i][j].source, screen, &_level[i][j].destination);

			_level[i][j].Draw(screen);


		}
	}
}


bool Level::Intersect(SDL_Rect r1, SDL_Rect r2)
{
	return !(r2.x > (r1.x + r1.w) || (r2.x + r2.w) < r1.x || r2.y > (r1.y + r1.h) || (r2.y + r2.h) < r1.y);
}


bool Level::IsCollidingWithBlock( SDL_Rect bound, int precsionX, int presionY)
{
	
	for (int i = (int)(bound.x / 32); i < (int)(bound.x / 32 + precsionX); i++) // here 32 = block width replace it with GameManager::getINstance()->blockWidth
	{
		for (int j = (int)(bound.y / 32); j < (int)(bound.y / 32 + presionY); j++) //here 32 = block height // replace blockHeight
		{
			if (i >= 0 && j >= 0 && i < 25 && j < 19)
			{
	

				if (_level[j][i].id == GameManager::getInstance()->solid)        //means if solid
				{
					

					if (Intersect(bound, _level[j][i].destination))       // column wise
					{

						return true;
					}
				}
			}

		}
	}
	return false;
}


bool Level::EatFoodBlock(int id, SDL_Rect bound, int precsionX, int presionY)
{
	for (int i = (int)(bound.x / 32); i < (int)(bound.x / 32 + precsionX); i++) // here 32 = block width replace it with GameManager::getINstance()->blockWidth
	{
		for (int j = (int)(bound.y / 32); j < (int)(bound.y / 32 + presionY); j++) //here 32 = block height // replace blockHeight
		{
			if (i >= 0 && j >= 0 && i < 25 && j < 19)
			{
				

				if (_level[j][i].id == id && _level[j][i].isActive)        
				{
					

					if (Intersect(bound, _level[j][i].destination))       // column wise
					{
						_level[j][i].isActive = false;
						
						
						return true;
					}
				}
			}

		}
	}
	return false;
}