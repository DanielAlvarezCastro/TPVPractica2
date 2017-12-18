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
public:
	virtual void update();
	SmartGhost(Game* dir);
	SmartGhost(Game *dir, uint xI, uint yI, uint FcolI);
	~SmartGhost();
	virtual void saveToFile(ofstream& archivo);
	virtual void loadFromFile(ifstream& archivo);
};

