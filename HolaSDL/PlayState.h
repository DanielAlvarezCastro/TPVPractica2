#pragma once
#include "GameState.h"

class PlayState:public GameState
{
private:
	
	int score;
	SDL_Color white;
	Font* screenFont;
	Texture* scoreText;
	SDL_Rect scorePos;

	uint level;
	UserInterface* userinterface;
public:
	PlayState(Game* g);
	~PlayState();
	Texture* pacmanText;
	MapCell getCell(int x, int y);

	void changeCell(int x, int y, MapCell cell);
	void addScore(int cuantity);
	void substractFood();
	void substractVitamin();

	void createMap(ifstream& filename);
	void loadLevel(string filename);
	void loadSave(string filename);
	void menuEvents();
	void nextLevel();
	void handleEvent(SDL_Event& e);
	void update();
	void render();
	void resetGame();

	bool nextCell(int x, int y, int dirX, int dirY, int& nx, int& ny);
	int pacmanColl();
	void handleCollision();
	vector<int>sghostCounter();
	void handleBirths();
	void resetPositions();
	void vulnerabilityOff();
	int getPacmanLives();

	void checkEndGame();
	void gameOver();
	void gameWon();
};

