#include "GameState.h"
#include "Game.h"


GameState::GameState(Game* g)
{
	game = g;
}


GameState::~GameState()
{
}

/*void GameState::Update()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->update();
	}
}
void GameState::Render()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->render();
	}
}

void GameState::handleEvent(SDL_Event& e){}*/
