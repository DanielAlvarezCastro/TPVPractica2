#include "EndState.h"
#include "Game.h"


EndState::EndState(Game* g, bool w) : GameState(g)
{
	win = w;
	gameOverText = new Texture();
	gameWonText = new Texture();
	quit = new Texture();
	quit2 = new Texture();
	menuFont = new Font("..\\fonts\\Quicksilver.ttf", 100);

	yellow.a = yellow.r = yellow.g = 255;
	yellow.b = 0;

	quitB.h = 50;
	quitB.w = 100;
	quitB.x = 650;
	quitB.y = 500;

	quitB2.h = 50;
	quitB2.w = 150;
	quitB2.x = 75;
	quitB2.y = 500;

	quit->loadFromText(game->renderer, "exit", menuFont, yellow);
	quit2->loadFromText(game->renderer, "Main Menu", menuFont, yellow);
	gameOverText->load(game->renderer, "..\\images\\gameOver.png");
	gameWonText->load(game->renderer, "..\\images\\gameWon.png");
	windowRect.x = windowRect.y = 0;
	windowRect.w = game->getWinW();
	windowRect.h = game->getWinH();
}


EndState::~EndState()
{
	delete gameOverText;
	delete gameWonText;
	delete quit;
	delete quit2;
	delete menuFont;
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
		quit->render(game->renderer, quitB);
		quit2->render(game->renderer, quitB2);
	}
}
void EndState::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		SDL_GetMouseState(&mouse.x, &mouse.y);
		if (SDL_PointInRect(&mouse, &quitB))
		{
			game->exit = true;
		}
		else if (SDL_PointInRect(&mouse, &quitB2))
		{
			game->returnToMenu();
		}
	}
}
