#include "SmartGhost.h"
#include "Game.h"


SmartGhost::SmartGhost(Game *dir, uint xI, uint yI, uint FcolI): Ghost(dir, xI, yI, FcolI)
{

	edad = 1;
	adulto = false;
	hIni = destRect.h;
	wIni = destRect.w;
	muerto = false;
}
SmartGhost::SmartGhost(Game *dir) : Ghost(dir)
{
	edad = 1;
	adulto = false;
	hIni = destRect.h;
	wIni = destRect.w;
	Fcol = IniFcol = 8;
	muerto = false;
}


SmartGhost::~SmartGhost()
{
}
void SmartGhost::saveToFile(ofstream& archivo)//Método de guardado en archivo
{
	archivo << "1" << " ";
	GameCharacter::saveToFile(archivo);
	archivo << edad << " ";
}
void SmartGhost::loadFromFile(ifstream& archivo)//Método de cargado en archivo
{
	Ghost::loadFromFile(archivo);
	archivo >> edad;
}

void SmartGhost::dirToPacman(){//Si está en la misma línea que Pacman lo sigue hasta que lo pierde 	

	int nx = 0;
	int ny = 0;
	par aux;
	aux.x = aux.y = 0;	
	if (game->p->getPosX() > x && game->nextCell(x, y, 1, 0, nx, ny) && game->p->getPosY() == y){//Solo añade la dirección si Pacman está a la derecha
		aux.x = 1;
		aux.y = 0;
		dir.push_back(aux);//Mete la dirección derecha al vector si es posible
		nx = ny = 0;
	}
	else if (game->p->getPosX() <= x && game->nextCell(x, y, -1, 0, nx, ny) && game->p->getPosY() == y){//Solo añade la dirección si Pacman está a la izquierda
		aux.x = -1;
		aux.y = 0;
		dir.push_back(aux);
		nx = ny = 0;
	}
	else if (game->p->getPosY() > y && game->nextCell(x, y, 0, 1, nx, ny) && game->p->getPosX() == x){//Solo añade la dirección si Pacman está abajo
		aux.x = 0;
		aux.y = 1;
		dir.push_back(aux);
		nx = ny = 0;
	}
	else if (game->p->getPosY() <= y && game->nextCell(x, y, 0, -1, nx, ny) && game->p->getPosX() == x){//Solo añade la dirección si Pacman está arriba
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
	if (game->nextCell(x, y, 1, 0, nx, ny) && !(dirX == -1 && dirY == 0))//Comprueba derecha
	{
		aux.x = 1;
		aux.y = 0;
		dir.push_back(aux);//Mete la dirección derecha al vector si es posible
		
	}
	nx = ny = 0;
	if (game->nextCell(x, y, -1, 0, nx, ny) && !(dirX == 1 && dirY == 0))//Izquierda
	{
		aux.x = -1;
		aux.y = 0;
		dir.push_back(aux);
		
	}
	nx = ny = 0;
	if (game->nextCell(x, y, 0, 1, nx, ny) && !(dirX == 0 && dirY == -1))//Abajo
	{
		aux.x = 0;
		aux.y = 1;
		dir.push_back(aux);		
	}
	nx = ny = 0;
	if (game->nextCell(x, y, 0, -1, nx, ny) && !(dirX == 0 && dirY == 1))//Arriba
	{
		aux.x = 0;
		aux.y = -1;
		dir.push_back(aux);
		
	}
}
void SmartGhost::move()//Escoge una dirección aleatoria del vector y la aplica
{
	dirToPacman();//Comprueba si se puede mover hacia Pacman
	if (dir.size() == 0)//Si el tamaño del vector es 0, pone a 0 las direcciones para que vuelva a buscar entre las direcciones disponibles
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
	if (x >= game->getCols())//Estas condiciones hacen que el mapa tenga forma toroide
	{
		x = 0;
	}
	else if (x < 0)
	{
		x = game->getCols() - 1;
	}
	if (y < 0)
	{
		y = game->getRows() - 1;
	}
	else if (y >= game->getRows())
	{
		y = 0;
	}
	dir.clear();//Limpia el vector de direcciones
}
void SmartGhost::ageManager(){
	if (edad < 100 && !adulto){
		edad++;
		destRect.h = hIni*edad / 100;
		destRect.w = wIni*edad / 100;
	}
	else if (edad >= 100)
	{
		edad++;
		adulto = true;
	}
	if (edad >= 110){
		vulnerabilityOn();
		muerto = true;
	}
}
void SmartGhost::update()
{	
	if (!muerto){
		move();		
	}
	destRect.x = x*w;
	destRect.y = y*h;
	Ghost::handleVulnerability();
	ageManager();
}

