#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Pacman.h"
#include "GameMap.h"
#include "Ghost.h"
#include "UserInterface.h"
#include "SmartGhost.h"
#include <string>
#include <iostream>
#include "GameObject.h"
#include "checkML.h";
#include <typeinfo>

using namespace std;
class Game
{
private:
	SDL_Window* window;
	bool error = false;//Flag para errores
	bool exit = false;
	bool exitMenu = false;
	bool exitlevel = false;
	bool gameover = false;

	SDL_Event event;

	int score;
	SDL_Color white;
	Font* screenFont;
	Texture* scoreText;
	SDL_Rect scorePos;

	bool saving = false;
	string codeN;
	Texture* savePanel;
	Texture* saveText;
	Texture* saveCode;
	SDL_Rect spanelPos;
	SDL_Rect stextPos;
	SDL_Rect scodePos;

	int winX, winY;
	const int winWidth = 800;
	const int winHeight = 600;


	uint level;
	UserInterface* userinterface;

public:
	//GameMap* gamemap;

	vector<GameObject*>gameObjects;
	//Entidades
	/*Pacman* pacman;
	SmartGhost* redGhost;
	Ghost* orangeGhost;
	Ghost* blueGhost;
	Ghost* purpleGhost;*/


	//Texturas
	Texture* pacmanText;
	//Fin Texturas

	SDL_Renderer* renderer;
	Game();
	~Game();
	int getWinW();
	int getWinH();
	int getRows();
	int getCols();
	MapCell getCell(int x, int y);


	void changeCell(int x, int y, MapCell cell);
	void addScore(int cuantity);
	void substractFood();
	void substractVitamin();

	void createMap(string filename);
	void menuEvents();
	void nextLevel();
	void handleEvents();
	void update();
	void render();
	void run();


	bool nextCell(int x, int y, int dirX, int dirY, int& nx, int& ny);
	int pacmanColl();
	/*bool PacmanBlueColl();
	bool PacmanRedColl();
	bool PacmanPurpleColl();
	bool PacmanOrangeColl();*/
	void handleCollision();
	void resetPositions();
	void vulnerabilityOff();
	int getPacmanLives();

	void checkEndGame();
	void gameOver();
	void gameWon();
};

