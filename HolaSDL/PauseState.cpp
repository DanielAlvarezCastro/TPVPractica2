#include "PauseState.h"
#include "Game.h"


PauseState::PauseState(Game* g):GameState(g)
{
	saveCode = new Texture();
	saveText = new Texture();
	savePanel = new Texture();
	quit = new Texture();
	screenFont = new Font("..\\fonts\\Kiloton v1.0.ttf", 50);
	savePanel->load(game->renderer, "..\\images\\bluePanel.png", 1, 1);
	saveText->loadFromText(game->renderer, "Create save code", screenFont, white);
	quit->loadFromText(game->renderer, "Main Menu", screenFont, white);

	white.a = 255;
	white.g = 255;
	white.b = 255;
	white.r = 255;

	quitB.h = 50;
	quitB.w = 100;
	quitB.x = 650;
	quitB.y = 500;

	spanelPos.h = 200;
	stextPos.h = 50;
	scodePos.h = 100;

	spanelPos.w = 400;
	stextPos.w = 200;
	scodePos.w = 300;

	scodePos.x = 270;
	spanelPos.x = 250;
	stextPos.x = 270;

	spanelPos.y = 200;
	stextPos.y = 220;
	scodePos.y = 300;

	goMenu = new MenuButton(game, quit, quitB, menu);
	gameObjects.push_back(goMenu);
}


PauseState::~PauseState()
{
	delete savePanel;
	delete saveText;
	delete saveCode;
	delete screenFont;
	delete quit;
	delete goMenu;
}
void PauseState::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == SDLK_0){
			codeN += "0";
			saveCode->loadFromText(game->renderer, codeN, screenFont, white);
		}
		else if (e.key.keysym.sym == SDLK_1){
			codeN += "1";
			saveCode->loadFromText(game->renderer, codeN, screenFont, white);
		}
		else if (e.key.keysym.sym == SDLK_2){
			codeN += "2";
			saveCode->loadFromText(game->renderer, codeN, screenFont, white);
		}
		else if (e.key.keysym.sym == SDLK_3){
			codeN += "3";
			saveCode->loadFromText(game->renderer, codeN, screenFont, white);
		}
		else if (e.key.keysym.sym == SDLK_4){
			codeN += "4";
			saveCode->loadFromText(game->renderer, codeN, screenFont, white);
		}
		else if (e.key.keysym.sym == SDLK_5){
			codeN += "5";
			saveCode->loadFromText(game->renderer, codeN, screenFont, white);
		}
		else if (e.key.keysym.sym == SDLK_6){
			codeN += "6";
			saveCode->loadFromText(game->renderer, codeN, screenFont, white);
		}
		else if (e.key.keysym.sym == SDLK_7){
			codeN += "7";
			saveCode->loadFromText(game->renderer, codeN, screenFont, white);
		}
		else if (e.key.keysym.sym == SDLK_8){
			codeN += "8";
			saveCode->loadFromText(game->renderer, codeN, screenFont, white);
		}
		else if (e.key.keysym.sym == SDLK_9){
			codeN += "9";
			saveCode->loadFromText(game->renderer, codeN, screenFont, white);
		}
		else if (e.key.keysym.sym == SDLK_RETURN)
		{
			game->saveResume(codeN);
		}
		else if (e.key.keysym.sym == SDLK_ESCAPE)
		{
			game->resume();
		}


	}
	else if (e.type == SDL_MOUSEBUTTONDOWN)
	{

		for (int i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i]->handleEvent(e);
		}
	}
}

void PauseState::render()
{
	savePanel->render(game->renderer, spanelPos);
	saveText->render(game->renderer, stextPos);
	saveCode->render(game->renderer, scodePos);
	quit->render(game->renderer, quitB);
}

void PauseState::menu(Game* game)
{
	game->returnToMenu();
}
