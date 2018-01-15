#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Texture.h"
#include "checkML.h";
#include "GameCharacter.h"
using namespace std;
class Pacman: public GameCharacter
{
private:
	int lives;
public:
	Pacman(Game *dir, PlayState* pS, uint xI, uint yI, uint Fcol);
	Pacman(Game* dir, PlayState* pS);
	~Pacman();
	virtual void saveToFile(ofstream& archivo);
	virtual void loadFromFile(ifstream& archivo);
	int getLives();
	int getPosX();
	int getPosY();

	void handleAnimation();
	void upAnimation();
	void downAnimation();
	void leftAnimation();
	void rightAnimation();

	void changeDir(char dir);
	void move();
	virtual void update();

	void die();

};

