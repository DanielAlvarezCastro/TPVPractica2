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
	bool muerto;
public:
	virtual void update();
	void dirToPacman();
	virtual void searchDir();
	virtual void move();
	SmartGhost(Game* dir);
	SmartGhost(Game *dir, uint xI, uint yI, uint FcolI);
	~SmartGhost();
	void ageManager();
	virtual void saveToFile(ofstream& archivo);
	virtual void loadFromFile(ifstream& archivo);
};

