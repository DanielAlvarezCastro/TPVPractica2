#include "GameCharacter.h"
#include "Game.h"



GameCharacter::GameCharacter(Game *g, PlayState* pS, uint xI, uint yI) :PacManObject(g, pS)
{
	texture = pState->pacmanText;
	Frow = IniFrow = 0;
	x = xIni = xI;
	y = yIni = yI;
	destRect.w = w = game->getWinW() / pState->getCols();//Calcula el tamaño del Pacman teniendo en relación la anchura de la ventana y las columnas
	destRect.h = h = game->getWinH() / pState->getRows();
	destRect.x = xIni*w;
	destRect.y = yIni*h;
	dirY = 1;

}
GameCharacter::GameCharacter(Game *g, PlayState* pS) :PacManObject(g, pS)
{
	texture = pState->pacmanText;
	Frow = IniFrow = 0;
	destRect.w = w = game->getWinW() / pState->getCols();//Calcula el tamaño del Pacman teniendo en relación la anchura de la ventana y las columnas
	destRect.h = h = game->getWinH() / pState->getRows();
	dirY = 1;

}


GameCharacter::~GameCharacter()
{
}
void GameCharacter::saveToFile(ofstream& archivo)//Método de guardado en archivo
{
	archivo << x << " " << y << " " << xIni << " " << yIni << " " << dirX << " " << dirY<<" ";
}
void GameCharacter::loadFromFile(ifstream& archivo)//Método de cargado en archivo
{
	archivo >> x;
	archivo >> y;
	if (x < 0 || y < 0)
	{
		throw FileFormatError("Posicion de GameCharacter invalida");
	}
	archivo >> xIni;
	archivo >> yIni;
	if (xIni < 0 || yIni < 0)
	{
		throw FileFormatError("Posicion inicial de GameCharacter invalida");
	}
	archivo >> dirX;
	archivo >> dirY;
	if (dirX < -1 || dirX>1 || dirY < -1 || dirY>1)
	{
		throw FileFormatError("Direciones de GameCharacter invalidas");
	}
	else if ((dirX == 1 && dirY == 1) || (dirX == -1 && dirY == -1))
	{
		throw FileFormatError("Direcion diagonal de GameCharacter invalidas");
	}
	destRect.x = xIni*w;
	destRect.y = yIni*h;



}
void GameCharacter::render()//Renderizado de los personajes del juego
{
	texture->renderFrame(game->renderer, srcRect, destRect, Frow, Fcol);
}
void GameCharacter::backToIni(){//Regresa a la posición inicial
	x = xIni;
	y = yIni;
}