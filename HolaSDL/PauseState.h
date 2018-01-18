#pragma once
#include "GameState.h"
#include "Texture.h"
#include "MenuButton.h"
class PauseState:public GameState
{
private:
	string codeN;
	Texture* savePanel;
	Texture* saveText;
	Texture* saveCode;
	SDL_Rect spanelPos;
	SDL_Rect stextPos;
	SDL_Rect scodePos;
	Texture* quit;
	SDL_Rect quitB;

	MenuButton* goMenu;

	SDL_Color white;
	Font* screenFont;
	SDL_Point mouse;


public:
	PauseState(Game* g);
	~PauseState();
	void handleEvent(SDL_Event& e);
	void render();
	void update(){};
	static void menu(Game* game);
};

