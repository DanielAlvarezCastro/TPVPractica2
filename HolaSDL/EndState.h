#pragma once
#include "GameState.h"

class EndState: public GameState
{
private:
	Texture* gameOverText;
	Texture* gameWonText;
	SDL_Rect windowRect;
	bool win;
public:
	EndState(Game* g, bool w);
	~EndState();
	void render();
	void handleEvent(SDL_Event& e);
};

