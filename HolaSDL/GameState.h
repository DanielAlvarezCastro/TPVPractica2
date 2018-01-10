#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <vector>
#include "GameObject.h"
#include "SDL_ttf.h"

using namespace std;
class Game;
class GameState
{
protected:
	vector<GameObject*>gameObjects;
	Game* game;
public:
	GameState(Game* g);
	~GameState();
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void handleEvent(SDL_Event& e) = 0;
};

