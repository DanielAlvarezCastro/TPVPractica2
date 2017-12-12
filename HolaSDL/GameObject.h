#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Game.h"

using namespace std;
class GameObject
{
protected:
	Game* game;
	virtual ~GameObject();

public:
	GameObject(/*Game *g*/);
	virtual void render();
	virtual void update();
	virtual void saveToFile();
	virtual void loadFromFile();
};

