#include "SmartGhost.h"


SmartGhost::SmartGhost(Game *dir, uint xI, uint yI, uint FcolI): Ghost(dir, xI, yI, FcolI)
{

	edad = 1;
	adulto = false;
	hIni = destRect.h;
	wIni = destRect.w;
}
SmartGhost::SmartGhost(Game *dir) : Ghost(dir)
{

}


SmartGhost::~SmartGhost()
{
}
void SmartGhost::saveToFile(ofstream& archivo){}//Método de guardado en archivo
void SmartGhost::loadFromFile(ifstream& archivo)//Método de cargado en archivo
{
	Ghost::loadFromFile(archivo);
	archivo >> edad;
}

void SmartGhost::update()
{
	Ghost::update();
	if (edad < 100 && !adulto){
		edad++;
		destRect.h = hIni*edad / 100;
		destRect.w = wIni*edad / 100;
	}
	else
	{
		adulto = true;
	}

}

