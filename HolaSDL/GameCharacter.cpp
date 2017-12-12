#include "GameCharacter.h"


GameCharacter::GameCharacter(uint xI, uint yI, uint FcolI)
{
	texture = game->pacmanText;
	Fcol = IniFcol = FcolI;
	Frow = IniFrow = 0;
	x = xIni = xI;
	y = yIni = yI;
	destRect.w = w = game->getWinW() / game->getCols();//Calcula el tamaño del Pacman teniendo en relación la anchura de la ventana y las columnas
	destRect.h = h = game->getWinH() / game->getRows();
	destRect.x = xIni*w;
	destRect.y = yIni*h;
	dirY = 1;

}


GameCharacter::~GameCharacter()
{
}
void GameCharacter::saveToFile(){}
void GameCharacter::loadFromFile(){}
void GameCharacter::render()
{
	texture->renderFrame(game->renderer, srcRect, destRect, Frow, Fcol);
}
void GameCharacter::update(){}