#pragma once
#include "Ghost.h"

class Game;
class SmartGhost: public Ghost
{
private:
	int edad;
	int hIni;
	int wIni;
	bool adulto;
	bool fertil;
	bool muerto;
public:
	virtual void update();
	void dirToPacman();
	virtual void searchDir();
	virtual void move();
	SmartGhost(Game* dir, PlayState* pS);
	SmartGhost(Game *dir, PlayState* pS, uint xI, uint yI);
	~SmartGhost();
	bool dead();
	bool getFertil();
	void fertilOff();
	void ageManager();
	virtual void saveToFile(ofstream& archivo);
	virtual void loadFromFile(ifstream& archivo);
};

