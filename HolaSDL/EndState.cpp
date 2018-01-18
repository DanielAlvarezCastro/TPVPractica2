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

	menu = new MenuButton(game, quit2, quitB2, goMenu);
	exit = new MenuButton(game, quit, quitB, exitGame);
	gameObjects.push_back(menu);
	gameObjects.push_back(exit);
}


EndState::~EndState()
{
	delete gameOverText;
	delete gameWonText;
	delete quit;
	delete quit2;
	delete menuFont;
	delete menu;
	delete exit;
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
		for (int i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i]->handleEvent(e);
		}
	}
		
}
void EndState::goMenu(Game* game)
{
	game->returnToMenu();
}
void EndState::exitGame(Game* game)
{
	game->exit = true;
}
