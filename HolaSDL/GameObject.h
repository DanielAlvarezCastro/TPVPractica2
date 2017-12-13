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
	GameObject();
	GameObject(Game *g);
	virtual void render()=0;
	virtual void update()=0;
	virtual void saveToFile()=0;
	virtual void loadFromFile()=0;
};

