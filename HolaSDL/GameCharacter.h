#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "GameObject.h"
#include "Texture.h"
using namespace std;
class GameCharacter: public GameObject
{
private:
	Texture* texture;
protected:
	virtual ~GameCharacter();
	int x, y, w, h, xIni, yIni;
	int nx, ny;//La posici�n siguiente calculada
	int dirX, dirY, ndirX, ndirY;
	uint Frow, Fcol;//Columnas donde est�n los frames en la imagen fuente
	uint IniFrow, IniFcol; //Columnas iniciales donde est�n los frames
	SDL_Rect destRect, srcRect;
public:
	GameCharacter(Game* g);
	GameCharacter(Game *g, uint xI, uint yI);
	virtual void update()=0;//Abstracto
	virtual void render();
	virtual void saveToFile(ofstream& archivo);
	virtual void loadFromFile(ifstream& archivo);
	virtual void backToIni();
};

