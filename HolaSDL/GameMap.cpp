#include "GameMap.h"
#include "Game.h"


GameMap::GameMap(Game* dir, uint rows, uint cols) : GameObject(dir)
{
	this->rows = rows;
	this->cols = cols;
	foods = 0;
	walls = 0;
	vitamins = 0;
	cells = new MapCell*[rows];
	for (int r = 0; r < rows; r++){
		cells[r] = new MapCell[cols];
	}
	size.h = game->getWinH() / rows;
	size.w = game->getWinW() / cols;
}

GameMap::~GameMap()
{
	if (cells != nullptr){
		for (int r = 0; r < rows; r++){
			delete[] cells[r];
		}
		delete[] cells;
	}
	delete WallTex;
	delete FoodTex;
	delete VitaminTex;
}
int GameMap::getRows(){//Pide las filas
	return rows;
}
int GameMap::getCols(){//Pide las columnas
	return cols;
}
int GameMap::getWalls(){//Pide paredes
	return walls;
}
int GameMap::getFoods(){//Pide n�mero de comida
	return foods;
}
int GameMap::getVitamins(){//Pide n�mero de vitaminas
	return vitamins;
}
void GameMap::mapTexts()//Cambia el tama�o de los vectores de texturas y las carga
{
	WallTex = new Texture();
	FoodTex = new Texture();
	VitaminTex = new Texture();
	WallTex->load(game->renderer, "..\\images\\wall2.png", 1, 1);
	FoodTex->load(game->renderer, "..\\images\\food2.png", 1, 1);
	VitaminTex->load(game->renderer, "..\\images\\burguer1.png", 1, 1);
}
void GameMap::render()//Pinta el mapa
{
	uint w = 0;
	uint f = 0;
	uint v = 0;
	SDL_Rect rect;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (cells[i][j] == Wall)
			{
				rect.h = size.h;
				rect.w = size.w;
				rect.x = j*size.w;
				rect.y = i*size.h;
				WallTex->render(game->renderer, rect);
				w++;

			}
			else if (cells[i][j] == Food)
			{
				rect.h = size.h;
				rect.w = size.w;
				rect.x = j*size.w;
				rect.y = i*size.h;
				FoodTex->render(game->renderer, rect);
				f++;

			}
			else if (cells[i][j] == Vitamins)
			{
				rect.h = size.h;
				rect.w = size.w;
				rect.x = j*size.w;
				rect.y = i*size.h;
				VitaminTex->render(game->renderer, rect);
				v++;

			}
		}
	}
}
void GameMap::saveToFile(){}//M�todo de guardado en archivo
void GameMap::loadFromFile(){}//M�todo de cargado en archivo
void GameMap::update(){}
