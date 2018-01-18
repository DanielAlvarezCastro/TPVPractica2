#include "MainMenuState.h"
#include "Game.h"


MainMenuState::MainMenuState(Game* g) : GameState(g)
{
	saving = false;
	codeN = "";
	backGround = new Texture();
	title = new Texture();
	option1 = new Texture();
	option2 = new Texture();
	quit = new Texture();

	bgPos.x = bgPos.y = 0;
	bgPos.h = game->getWinH();
	bgPos.w = game->getWinW();
	quitB.h = 50;
	quitB.w = 100;
	quitB.x = 650;
	quitB.y = 500;
	titlePos.h = 200;
	titlePos.w = 600;
	titlePos.x = 100;
	titlePos.y = 100;
	optionPos.h = optionPos2.h = 100;
	optionPos.w = optionPos2.w = 400;
	optionPos.x = optionPos2.x = 200;
	optionPos.y = 350;
	optionPos2.y = 475;
	yellow.a = yellow.r = yellow.g = 255;
	yellow.b = 0;

	menuFont = new Font("..\\fonts\\Quicksilver.ttf", 100);
	try{

		backGround->load(game->renderer, "..\\images\\bluePanel.png", 1, 1);
		title->loadFromText(game->renderer, "PACMAN", menuFont, yellow);
		option1->loadFromText(game->renderer, "New Game", menuFont, yellow);
		option2->loadFromText(game->renderer, "Load File", menuFont, yellow);
		quit->loadFromText(game->renderer, "exit", menuFont, yellow);
	}
	catch (SDLError& e)
	{
		cout << e.what() << endl;
	}

	op1 = new MenuButton(game, option1, optionPos,playState);
	exit = new MenuButton(game, quit, quitB, exitGame);
	

	gameObjects.push_back(op1);
	gameObjects.push_back(exit);
}


MainMenuState::~MainMenuState()
{
	delete quit;
	delete backGround;
	delete title;
	delete option1;
	delete option2;
	delete menuFont;
	delete exit;
	delete op1;
}

void MainMenuState::render()
{
	SDL_RenderClear(game->renderer);
	backGround->render(game->renderer, bgPos);
	title->render(game->renderer, titlePos);
	option1->render(game->renderer, optionPos);
	option2->render(game->renderer, optionPos2);
	quit->render(game->renderer, quitB);
	SDL_RenderPresent(game->renderer);
}
void MainMenuState::handleEvent(SDL_Event& e)
{
	if (!saving){
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			SDL_GetMouseState(&mouse.x, &mouse.y);
			if (SDL_PointInRect(&mouse, &optionPos2))
			{
				saving = true;
				titlePos.h = 100;
				optionPos.y = 275;
				title->loadFromText(game->renderer, "Enter save code", menuFont, yellow);
				option1->loadFromText(game->renderer, " ", menuFont, yellow);
				option1->render(game->renderer, optionPos);
				option2->loadFromText(game->renderer, "Press Enter", menuFont, yellow);
			}
			for (int i = 0; i < gameObjects.size(); i++)
			{
				gameObjects[i]->handleEvent(e);
			}
		}
	}
	else
		{
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_0){
					codeN += "0";
				}
				else if (e.key.keysym.sym == SDLK_1){
					codeN += "1";
				}
				else if (e.key.keysym.sym == SDLK_2){
					codeN += "2";
				}
				else if (e.key.keysym.sym == SDLK_3){
					codeN += "3";
				}
				else if (e.key.keysym.sym == SDLK_4){
					codeN += "4";
				}
				else if (e.key.keysym.sym == SDLK_5){
					codeN += "5";
				}
				else if (e.key.keysym.sym == SDLK_6){
					codeN += "6";
				}
				else if (e.key.keysym.sym == SDLK_7){
					codeN += "7";
				}
				else if (e.key.keysym.sym == SDLK_8){
					codeN += "8";
				}
				else if (e.key.keysym.sym == SDLK_9){
					codeN += "9";
				}
				else if (e.key.keysym.sym == SDLK_RETURN)
				{
					try{
						ifstream f("..\\saves\\" + codeN + ".pac");
						if (f.good()){
							game->playLoad(codeN);
						}
						else
						{
							throw FileNotFoundError(codeN);
						}
					}
					catch (FileNotFoundError& e)
					{
						cout << e.what() << endl;
						codeN = " ";
					}
				}
				try{
					option1->loadFromText(game->renderer, codeN, menuFont, yellow);
				}
				catch (SDLError& e)
				{
					cout << e.what() << endl;
				}
			}
		}
}

void MainMenuState::playState(Game* game)
{
	game->playState();
}

void MainMenuState::exitGame(Game* game)
{
	game->exit = true;
}


