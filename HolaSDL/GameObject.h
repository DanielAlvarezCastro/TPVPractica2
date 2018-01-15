#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <fstream>
class Game;
using namespace std;
class GameObject//Clase abstacta pura que engloba la jerarqu�a
{
protected:
	Game* game;

public:
	GameObject(Game *g);
	//Metodos abstractos
	virtual ~GameObject();
	virtual void render()=0;
	virtual void update()=0;

};

