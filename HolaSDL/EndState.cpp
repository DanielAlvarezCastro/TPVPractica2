#include "EndState.h"
#include "Game.h"


EndState::EndState(Game* g, bool w) : GameState(g)
{
	win = w;
	gameOverText = new Texture();
	gameWonText = new Texture();
	gameOverText->load(game->renderer, "..\\images\\gameOver.png");
	gameWonText->load(game->renderer, "..\\images\\gameWon.png");
	windowRect.x = windowRect.y = 0;
	windowRect.w = game->getWinW();
	windowRect.h = game->getWinH();
}


EndState::~EndState()
{
}

void EndState::render()
{
	if (win)
	{
		gameWonText->render(game->renderer, windowRect);
	}
	else
	{
		gameOverText->render(game->renderer, windowRect);
	}
}
void EndState::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN)
	{
		SDL_Delay(1500);
		game->quitEndScreen();
	}
}
