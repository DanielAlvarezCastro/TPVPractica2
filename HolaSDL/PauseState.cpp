#include "PauseState.h"
#include "Game.h"


PauseState::PauseState(Game* g):GameState(g)
{
	saveCode = new Texture();
	saveText = new Texture();
	savePanel = new Texture();
	savePanel->load(game->renderer, "..\\images\\bluePanel.png", 1, 1);
	saveText->loadFromText(game->renderer, "Create save code", screenFont, white);

	white.a = 255;
	white.g = 255;
	white.b = 255;
	white.r = 255;

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
}


PauseState::~PauseState()
{
	delete savePanel;
	delete saveText;
	delete saveCode;
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

		}

	}
}

void PauseState::render()
{
	savePanel->render(game->renderer, spanelPos);
	saveText->render(game->renderer, stextPos);
	saveCode->render(game->renderer, scodePos);
}
