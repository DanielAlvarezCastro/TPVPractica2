#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Font.h"
#include "Texture.h"
#include "SDL_ttf.h"
#include "GameState.h"
class MainMenuState: public GameState
{
private:

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
	SDL_Point mouse;

	string codeN;
	bool saving;
public:

	MainMenuState(Game* g);
	~MainMenuState();
	void render();
	void handleEvent(SDL_Event& e);
	void update(){};
};

