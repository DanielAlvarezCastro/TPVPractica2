#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Pacman.h"
#include "GameMap.h"
#include "Ghost.h"
#include "UserInterface.h"
#include "SmartGhost.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "MainMenu.h"
#include "GameObject.h"
#include "checkML.h";
#include <typeinfo>
#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "PauseState.h"
#include "EndState.h"
#include "PlayState.h"
#include <stdexcept>

using namespace std;
class Game
{
private:
	SDL_Window* window;
	bool error = false;//Flag para errores
	bool exit = false;
	SDL_Event event;
	int winX, winY;
	const int winWidth = 800;
	const int winHeight = 600;
	GameStateMachine* stateMachine;

public:


	vector<GameObject*> gameObjects;
	Pacman* p;

	SDL_Renderer* renderer;
	Game();
	~Game();
	int getWinW();
	int getWinH();
	void handleEvents();
	void render();
	void run();

	void playState();
	void playLoad(string filename);
	void pause();
	void resume();
	void saveResume(string filename);
	void endScreen(bool win);
	void quitEndScreen();
};

