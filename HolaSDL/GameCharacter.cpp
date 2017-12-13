#include "GameCharacter.h"
#include "Game.h"


GameCharacter::GameCharacter(Game *g, uint xI, uint yI, uint FcolI):GameObject(g)
{
	texture = game->pacmanText;
	Fcol = IniFcol = FcolI;//Cordenadas dentro del SpriteSheet
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
void GameCharacter::saveToFile(){}//Método de guardado en archivo
void GameCharacter::loadFromFile(){}//Método de cargado en archivo
void GameCharacter::render()//Renderizado de los personajes del juego
{
	texture->renderFrame(game->renderer, srcRect, destRect, Frow, Fcol);
}