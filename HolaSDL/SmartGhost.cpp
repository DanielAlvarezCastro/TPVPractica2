#include "SmartGhost.h"
#include "Game.h"


SmartGhost::SmartGhost(Game *dir, PlayState* pS, uint xI, uint yI) :Ghost(dir,pS, xI, yI)
{

	edad = 1;
	adulto = false;
	fertil = false;
	hIni = destRect.h;
	wIni = destRect.w;
	Fcol = IniFcol = 8;
	muerto = false;
}
SmartGhost::SmartGhost(Game *dir, PlayState* pS) : Ghost(dir,pS, 8)
{
	edad = 1;
	adulto = false;
	fertil = false;
	hIni = destRect.h;
	wIni = destRect.w;
	muerto = false;
}


SmartGhost::~SmartGhost()
{
}
void SmartGhost::saveToFile(ofstream& archivo)//M�todo de guardado en archivo
{
	archivo << "1" << " ";
	GameCharacter::saveToFile(archivo);
	archivo << edad << " ";
}
void SmartGhost::loadFromFile(ifstream& archivo)//M�todo de cargado en archivo
{
	Ghost::loadFromFile(archivo);
	archivo >> edad;
}

bool SmartGhost::getFertil()
{
	if (fertil)
	{
		return true;
	}
	else { return false; }
}

void SmartGhost::fertilOff()
{
	fertil = false;
}

void SmartGhost::dirToPacman(){//Si est� en la misma l�nea que Pacman lo sigue hasta que lo pierde 	

	int nx = 0;
	int ny = 0;
	par aux;
	aux.x = aux.y = 0;	
	if (pState->p->getPosX() > x && pState->nextCell(x, y, 1, 0, nx, ny) && pState->p->getPosY() == y){//Solo a�ade la direcci�n si Pacman est� a la derecha
		aux.x = 1;
		aux.y = 0;
		dir.push_back(aux);//Mete la direcci�n derecha al vector si es posible
		nx = ny = 0;
	}
	else if (pState->p->getPosX() <= x && pState->nextCell(x, y, -1, 0, nx, ny) && pState->p->getPosY() == y){//Solo a�ade la direcci�n si Pacman est� a la izquierda
		aux.x = -1;
		aux.y = 0;
		dir.push_back(aux);
		nx = ny = 0;
	}
	else if (pState->p->getPosY() > y && pState->nextCell(x, y, 0, 1, nx, ny) && pState->p->getPosX() == x){//Solo a�ade la direcci�n si Pacman est� abajo
		aux.x = 0;
		aux.y = 1;
		dir.push_back(aux);
		nx = ny = 0;
	}
	else if (pState->p->getPosY() <= y && pState->nextCell(x, y, 0, -1, nx, ny) && pState->p->getPosX() == x){//Solo a�ade la direcci�n si Pacman est� arriba
		aux.x = 0;
		aux.y = -1;
		dir.push_back(aux);
	}
	

}
bool SmartGhost::dead(){
	return muerto;
}
void SmartGhost::searchDir(){

 	int nx = 0;
	int ny = 0;
	par aux;
	aux.x = aux.y = 0;	
	if (pState->nextCell(x, y, 1, 0, nx, ny) && !(dirX == -1 && dirY == 0))//Comprueba derecha
	{
		aux.x = 1;
		aux.y = 0;
		dir.push_back(aux);//Mete la direcci�n derecha al vector si es posible
		
	}
	nx = ny = 0;
	if (pState->nextCell(x, y, -1, 0, nx, ny) && !(dirX == 1 && dirY == 0))//Izquierda
	{
		aux.x = -1;
		aux.y = 0;
		dir.push_back(aux);
		
	}
	nx = ny = 0;
	if (pState->nextCell(x, y, 0, 1, nx, ny) && !(dirX == 0 && dirY == -1))//Abajo
	{
		aux.x = 0;
		aux.y = 1;
		dir.push_back(aux);		
	}
	nx = ny = 0;
	if (pState->nextCell(x, y, 0, -1, nx, ny) && !(dirX == 0 && dirY == 1))//Arriba
	{
		aux.x = 0;
		aux.y = -1;
		dir.push_back(aux);
		
	}
}
void SmartGhost::move()//Escoge una direcci�n aleatoria del vector y la aplica
{
	dirToPacman();//Comprueba si se puede mover hacia Pacman
	if (dir.size() == 0)//Si el tama�o del vector es 0, pone a 0 las direcciones para que vuelva a buscar entre las direcciones disponibles
	{
		searchDir();
	}
	if (dir.size() > 0){
		int r = rand() % dir.size();//Valor auxiliar que guarda el random
		dirX = dir[r].x;
		dirY = dir[r].y;
	}
	else{
		dirX = dirY = 0;
	}
	x += dirX;
	y += dirY;
	if (x >= pState->getCols())//Estas condiciones hacen que el mapa tenga forma toroide
	{
		x = 0;
	}
	else if (x < 0)
	{
		x = pState->getCols() - 1;
	}
	if (y < 0)
	{
		y = pState->getRows() - 1;
	}
	else if (y >= pState->getRows())
	{
		y = 0;
	}
	dir.clear();//Limpia el vector de direcciones
}
void SmartGhost::ageManager(){
	if (edad < 99 && !adulto){
		edad++;
		destRect.h = hIni*edad / 100;
		destRect.w = wIni*edad / 100;
	}
	else if (edad == 99)
	{
		fertil = true;
		edad++;
	}
	else if (edad >= 100)
	{
		edad++;
		adulto = true;
	}
	if (edad >= 300){
		vulnerabilityOn();
		muerto = true;
	}
}
void SmartGhost::update()
{
	if (!adulto)
	{
		Ghost::update();
	}
	else
	{
		if (!muerto){

			move();
		}
		destRect.x = x*w;
		destRect.y = y*h;
		Ghost::handleVulnerability();
	}
	ageManager();
}

