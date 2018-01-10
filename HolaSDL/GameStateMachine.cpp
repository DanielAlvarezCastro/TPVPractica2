#include "GameStateMachine.h"


GameStateMachine::GameStateMachine()
{
}


GameStateMachine::~GameStateMachine()
{
}

void GameStateMachine::currentState(){}

void GameStateMachine::pushState(GameState* ge)
{
	stateStack.push(ge);
}

void GameStateMachine::popState()
{
	stateStack.pop();
}

void GameStateMachine::changeState(GameState* ge)
{
	popState();
	pushState(ge);
}
