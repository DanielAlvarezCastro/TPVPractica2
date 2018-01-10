#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <stack>
#include "GameState.h"
class GameStateMachine
{
private:
	stack<GameState*>stateStack;
public:
	GameStateMachine();
	~GameStateMachine();
	void currentState();
	void pushState(GameState* ge);
	void changeState(GameState* ge);
	void popState();

};

