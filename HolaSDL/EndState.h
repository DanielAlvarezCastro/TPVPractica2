#pragma once
#include "GameState.h"
#include "MenuButton.h"

class EndState: public GameState
{
private:
	Texture* gameOverText;
	Texture* gameWonText;
	Texture* quit;
	Texture* quit2;
	SDL_Rect windowRect;
	bool win;

	SDL_Rect quitB;
	SDL_Rect quitB2;

	MenuButton* exit;
	MenuButton* menu;

	Font* menuFont;
	SDL_Color yellow;
	SDL_Point mouse;
public:
	EndState(Game* g, bool w);
	~EndState();
	void render();
	void handleEvent(SDL_Event& e);
	void update(){};
	static void goMenu(Game* game);
	static void exitGame(Game* game);
};

