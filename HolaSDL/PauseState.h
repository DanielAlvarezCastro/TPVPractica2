#pragma once
#include "GameState.h"
#include "Texture.h"
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

	SDL_Color white;
	Font* screenFont;


public:
	PauseState(Game* g);
	~PauseState();
	void handleEvent(SDL_Event& e);
	void render();
	void update(){};
};

