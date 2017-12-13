#include "GameCharacter.h"
#include "Game.h"


GameCharacter::GameCharacter(Game *g, uint xI, uint yI, uint FcolI):GameObject(g)
{
	texture = game->pacmanText;
	Fcol = IniFcol = FcolI;//Cordenadas dentro del SpriteSheet
	Frow = IniFrow = 0;
	x = xIni = xI;
	y = yIni = yI;
	destRect.w = w = game->getWinW() / game->getCols();//Calcula el tama�o del Pacman teniendo en relaci�n la anchura de la ventana y las columnas
	destRect.h = h = game->getWinH() / game->getRows();
	destRect.x = xIni*w;
	destRect.y = yIni*h;
	dirY = 1;

}


GameCharacter::~GameCharacter()
{
}
void GameCharacter::saveToFile(){}//M�todo de guardado en archivo
void GameCharacter::loadFromFile(){}//M�todo de cargado en archivo
void GameCharacter::render()//Renderizado de los personajes del juego
{
	texture->renderFrame(game->renderer, srcRect, destRect, Frow, Fcol);
}