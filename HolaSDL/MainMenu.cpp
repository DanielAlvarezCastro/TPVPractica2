#include "MainMenu.h"
#include "Game.h"


MainMenu::MainMenu(Game* g)
{
	game = g;
	exit = false;
	saving = false;
	codeN = "";
	backGround = new Texture();
	title = new Texture();
	option1 = new Texture();
	option2 = new Texture();

	bgPos.x = bgPos.y = 0;
	bgPos.h = game->getWinH();
	bgPos.w = game->getWinW();
	titlePos.h = 200;
	titlePos.w = 600;
	titlePos.x = 100;
	titlePos.y = 100;
	optionPos.h = optionPos2.h = 100;
	optionPos.w = optionPos2.w = 400;
	optionPos.x = optionPos2.x = 200;
	optionPos.y = 350;
	optionPos2.y = 475;
	yellow.a = yellow.b = yellow.g = 255;
	yellow.r = 0;

	menuFont = new Font("..\\fonts\\Quicksilver.ttf", 100);
	backGround->load(game->renderer, "..\\images\\bluePanel.png", 1, 1);
	title->loadFromText(game->renderer, "PACMAN", menuFont, yellow);
	option1->loadFromText(game->renderer, "New Game", menuFont, yellow);
	option2->loadFromText(game->renderer, "Load File", menuFont, yellow);


}


MainMenu::~MainMenu()
{
	delete backGround;
	delete title;
	delete option1;
	delete option2;
	delete menuFont;
}

void MainMenu::render()
{
	SDL_RenderClear(game->renderer);
	backGround->render(game->renderer, bgPos);
	title->render(game->renderer, titlePos);
	option1->render(game->renderer, optionPos);
	option2->render(game->renderer, optionPos2);
	SDL_RenderPresent(game->renderer);
}
void MainMenu::handleEvents()
{
	while (SDL_PollEvent(&event) && !exit)
	{
		if ((event.type == SDL_MOUSEBUTTONDOWN && !saving) || (event.type == SDL_KEYDOWN && saving))
		{
			if (!saving)
			{

				SDL_GetMouseState(&mouse.x, &mouse.y);
				if (SDL_PointInRect(&mouse, &optionPos))
				{
					exit = true;
				}
				else if (SDL_PointInRect(&mouse, &optionPos2))
				{
					saving = true;
					titlePos.h = 100;
					optionPos.y = 275;
					title->loadFromText(game->renderer, "Enter save code", menuFont, yellow);
					option1->loadFromText(game->renderer, " ", menuFont, yellow);
					option1->render(game->renderer, optionPos);
					option2->loadFromText(game->renderer, "Press Enter", menuFont, yellow);
				}
			}
			else
			{
				if (event.key.keysym.sym == SDLK_0){
					codeN += "0";
					option1->loadFromText(game->renderer, codeN, menuFont, yellow);
				}
				else if (event.key.keysym.sym == SDLK_1){
					codeN += "1";
					option1->loadFromText(game->renderer, codeN, menuFont, yellow);
				}
				else if (event.key.keysym.sym == SDLK_2){
					codeN += "2";
					option1->loadFromText(game->renderer, codeN, menuFont, yellow);
				}
				else if (event.key.keysym.sym == SDLK_3){
					codeN += "3";
					option1->loadFromText(game->renderer, codeN, menuFont, yellow);
				}
				else if (event.key.keysym.sym == SDLK_4){
					codeN += "4";
					option1->loadFromText(game->renderer, codeN, menuFont, yellow);
				}
				else if (event.key.keysym.sym == SDLK_5){
					codeN += "5";
					option1->loadFromText(game->renderer, codeN, menuFont, yellow);
				}
				else if (event.key.keysym.sym == SDLK_6){
					codeN += "6";
					option1->loadFromText(game->renderer, codeN, menuFont, yellow);
				}
				else if (event.key.keysym.sym == SDLK_7){
					codeN += "7";
					option1->loadFromText(game->renderer, codeN, menuFont, yellow);
				}
				else if (event.key.keysym.sym == SDLK_8){
					codeN += "8";
					option1->loadFromText(game->renderer, codeN, menuFont, yellow);
				}
				else if (event.key.keysym.sym == SDLK_9){
					codeN += "9";
					option1->loadFromText(game->renderer, codeN, menuFont, yellow);
				}
				else if (event.key.keysym.sym == SDLK_RETURN)
				{
					exit = true;
				}
			}
		}
	}
}