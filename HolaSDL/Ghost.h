#pragma once
#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Texture.h"
#include "GameMap.h"
#include  <cstdlib>
#include <time.h>
#include "checkML.h"
#include "GameCharacter.h"

struct par{//Struct para guardar las direcciones
	int x;
	int y;
};

using namespace std;
class Ghost: public GameCharacter
{
protected:
	vector<par> dir;//Vector que guarda las direcciones accesibles
	uint bFrow, bFcol;//Filas y columnas de los sprites azules
	bool vulnerable;//Booleano que indica si el fantasma se puede comer o no
	clock_t startTime;

public:
	Ghost(Game *dir,PlayState* pS, uint xI, uint yI);
	Ghost(Game* dir, PlayState* pS, int iCol);
	~Ghost();
	virtual void saveToFile(ofstream& archivo);
	virtual void loadFromFile(ifstream& archivo);

	int getPosX();
	int getPosY();
	bool getVulnerability();

	void blueAnimation();
	void standardAnimation();

	void vulnerabilityOn();
	void vulnerabilityOff();
	void handleVulnerability();

	void searchDir();
	void move();
	virtual void update();
};

