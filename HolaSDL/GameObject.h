#pragma once
#include "SDL.h"
#include "SDL_image.h"
class Game;
using namespace std;
class GameObject//Clase abstacta pura que engloba la jerarquía
{
protected:
	Game* game;
	virtual ~GameObject();

public:
	GameObject(Game *g);
	//Metodos abstractos
	virtual void render()=0;
	virtual void update()=0;
	virtual void saveToFile()=0;
	virtual void loadFromFile()=0;
};

