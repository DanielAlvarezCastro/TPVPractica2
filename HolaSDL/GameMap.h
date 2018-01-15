#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Texture.h"
#include "checkML.h";
#include <vector>
#include "GameObject.h"
#include "PacManObject.h"
using namespace std;
enum MapCell{ Empty, Wall, Food, Vitamins };
class Game;
class GameMap: public PacManObject
{
	friend class Game;
private:
	Texture* WallTex;
	Texture* FoodTex;
	Texture* VitaminTex;
	SDL_Rect size;
	uint rows;
	uint cols;
	uint walls;

public:

	uint foods;
	uint vitamins;
	MapCell** cells;
	GameMap(Game* dir, PlayState* pS, uint rows, uint cols);
	GameMap(Game* dir, PlayState* pS);
	~GameMap();
	int getRows();
	int getCols();
	int getWalls();
	int getFoods();
	int getVitamins();

	virtual void saveToFile(ofstream& archivo);
	virtual void loadFromFile(ifstream& archivo);
	virtual void update() {};
	void mapTexts();
	virtual void render();
};

