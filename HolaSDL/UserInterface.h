
#include "SDL.h"
#include "SDL_image.h"
#include "Texture.h"
#include "GameMap.h"
#include "checkML.h";
#pragma once
class Game;
class PlayState;
class UserInterface
{
private:
	Texture* menuText;
	Texture* levelCText;
	Texture* gameOverText;
	Texture* gameWonText;
	Texture* life;
	SDL_Rect lifeSrcRect;
	SDL_Rect lifeRect;
	SDL_Rect windowRect;
	PlayState* pState;
	Game* game;
public:
	UserInterface(Game* dir, PlayState* pS);
	void menuRender();
	void setLifeSize();
	void renderLives();
	void nextLevelRender();
	void gameOverRender();
	void gameWonRender();
	~UserInterface();
};

