#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <vector>
#include "GameObject.h"
#include "SDL_ttf.h"
#include "UserInterface.h"

using namespace std;
class Game;
class GameState
{
protected:
	vector<GameObject*>gameObjects;
	Game* game;
public:
	GameState(Game* g);
	virtual ~GameState();
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void handleEvent(SDL_Event& e) = 0;
};

