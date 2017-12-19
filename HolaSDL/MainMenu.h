#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Font.h"
#include "Texture.h"
#include "SDL_ttf.h"

using namespace std;
class Game;
class MainMenu
{
private:
	Game* game;

	Texture* backGround;
	Texture* title;
	Texture* option1;
	Texture* option2;

	SDL_Rect bgPos;
	SDL_Rect titlePos;
	SDL_Rect optionPos;
	SDL_Rect optionPos2;

	Font* menuFont;
	SDL_Color yellow;
	SDL_Event event;
	SDL_Point mouse;
	
public:
	MainMenu(Game* g);
	~MainMenu();
	string codeN;
	bool saving;
	bool exit;
	void render();
	void handleEvents();

};

