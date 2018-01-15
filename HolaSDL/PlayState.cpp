#include "PlayState.h"
#include "Game.h"


PlayState::PlayState(Game* g) : GameState(g)
{
	level = 1;
	score = 0;
	userinterface = new UserInterface(game, this);

	//Inicializa Textura del SpriteSheet
	pacmanText = new Texture();
	//Lo carga
	pacmanText->load(game->renderer, "..\\images\\characters1.png", 4, 14);
	screenFont = new Font("..\\fonts\\Kiloton v1.0.ttf", 50);
	//Inicializa Texturas de Interfaz
	scoreText = new Texture();

	white.a = 255;
	white.g = 255;
	white.b = 255;
	white.r = 255;

	scorePos.h = 27;
	scorePos.w = 100;
	scorePos.x = 350;
	scorePos.y = 579;

	nextLevel();
}

PlayState::PlayState(Game* g, string filename) : GameState(g)
{
	level = 1;
	score = 0;
	userinterface = new UserInterface(game, this);

	//Inicializa Textura del SpriteSheet
	pacmanText = new Texture();
	//Lo carga
	pacmanText->load(game->renderer, "..\\images\\characters1.png", 4, 14);
	screenFont = new Font("..\\fonts\\Kiloton v1.0.ttf", 50);
	//Inicializa Texturas de Interfaz
	scoreText = new Texture();

	white.a = 255;
	white.g = 255;
	white.b = 255;
	white.r = 255;

	scorePos.h = 27;
	scorePos.w = 100;
	scorePos.x = 350;
	scorePos.y = 579;

	loadSave(filename);
}



PlayState::~PlayState()
{
	delete pacmanText;
	resetGame();
	delete userinterface;
	delete screenFont;
	delete scoreText;
}

void PlayState::resetGame()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		delete gameObjects[i];
	}
	gameObjects.clear();
}

MapCell PlayState::getCell(int x, int y)//Devuelve el valor que hay en una celda
{
	return static_cast<GameMap*>(gameObjects[0])->cells[y][x];//La representación en la celda es al contrario
}

void PlayState::changeCell(int x, int y, MapCell cell)//Cambia el valor de una celda, se usa en el pacman al comer una vitamina o comida y cambiarla por empty
{
	static_cast<GameMap*>(gameObjects[0])->cells[y][x] = cell;
}
void PlayState::substractFood()//Resta 1 al contador de comida
{
	addScore(10);
	static_cast<GameMap*>(gameObjects[0])->foods--;
}
void PlayState::substractVitamin()//Resta 1 al contador de vitamina
{
	addScore(50);
	static_cast<GameMap*>(gameObjects[0])->vitamins--;
}

void PlayState::nextLevel(){//Controla el nivel que se va a cargar

		loadLevel("level0" + to_string(level));
		userinterface->setLifeSize();
	

}
int PlayState::getRows()//Pide las filas
{
	return static_cast<GameMap*>(gameObjects[0])->getRows();
}
int PlayState::getCols()//Pide las columnas
{
	return static_cast<GameMap*>(gameObjects[0])->getCols();
}
void PlayState::loadSave(string filename)//Carga una partida guardada
{
	ifstream archivo;
	gameObjects.clear();
	archivo.open("..\\saves\\" + filename + ".pac");
	archivo >> level;
	archivo >> score;
	createMap(archivo);
	userinterface->setLifeSize();
}

void PlayState::loadLevel(string filename)//Carga un nivel nuevo
{
	ifstream archivo;
	resetGame();
	archivo.open("..\\levels\\" + filename + ".pac");
	createMap(archivo);
}
void PlayState::createMap(ifstream& archivo)//Lee de un archivo y crea la matriz del mapa
{
	int dato;
	GameMap* gm = new GameMap(game, this);
	gm->loadFromFile(archivo);
	int size;
	archivo >> size;
	size = size;
	gameObjects.push_back(gm);
	for (int i = 1; i <= size; i++)
	{
		archivo >> dato;
		if (dato == 1)
		{
			SmartGhost* sg = new SmartGhost(game, this);
			gameObjects.push_back(sg);
			dynamic_cast<PacManObject*>(gameObjects[i])->loadFromFile(archivo);
		}
		else
		{
			Ghost* g = new Ghost(game,this, (i % 4) * 2);
			gameObjects.push_back(g);
			dynamic_cast<PacManObject*>(gameObjects[i])->loadFromFile(archivo);
		}
	}
	p = new Pacman(game, this);
	gameObjects.push_back(p);
	dynamic_cast<PacManObject*>(gameObjects[gameObjects.size() - 1])->loadFromFile(archivo);
	archivo.close();
	update();
	render();
	SDL_Delay(1000);

}

void PlayState::saveGame(string filename)
{
	ofstream archivo("..\\saves\\" + filename + ".pac");
	archivo << level << " " << score << endl;
	dynamic_cast<PacManObject*>(gameObjects[0])->saveToFile(archivo);
	archivo << endl;
	archivo << gameObjects.size() - 2;
	archivo << endl;
	for (int i = 1; i < gameObjects.size(); i++)
	{
		dynamic_cast<PacManObject*>(gameObjects[i])->saveToFile(archivo);
		archivo << endl;
	}
}
void PlayState::addScore(int cuantity)//Añade puntuación y refresca el marcador
{
	score += cuantity;
	string scoreSTR = "Score:" + to_string(score) + " ";

	scoreText->loadFromText(game->renderer, scoreSTR, screenFont, white);
}
void PlayState::update(){//Controla los updates de las entidades y comprueba si ha habido una colisión
	for (int i = gameObjects.size() - 1; i >= 0; i--)
	{
		gameObjects[i]->update();
		if (i == gameObjects.size() - 1)
		{
			handleCollision();
		}
		else
		{
			handleBirths();
		}
	}

	handleCollision();
	checkEndGame();
}
void PlayState::render(){//Aplica el render del mapa, de las vidas, y de las entidades
	SDL_RenderClear(game->renderer);
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->render();
	}
	gameObjects[gameObjects.size() - 1]->render();

	scoreText->render(game->renderer, scorePos);
	userinterface->renderLives();
	SDL_RenderPresent(game->renderer);
}
bool PlayState::nextCell(int x, int y, int dirX, int dirY, int& nx, int& ny)//Si la siguiente posición es una pared devuelve false
{
	nx = x + dirX;//Calcula la posición siguiente
	ny = y + dirY;
	if (nx >= static_cast<GameMap*>(gameObjects[0])->getCols())//Estas condiciones hacen que el mapa tenga forma toroide
	{
		nx = 0;
	}
	else if (nx < 0)
	{
		nx = static_cast<GameMap*>(gameObjects[0])->getCols() - 1;
	}
	if (ny < 0)
	{
		ny = static_cast<GameMap*>(gameObjects[0])->getRows() - 1;
	}
	else if (ny >= static_cast<GameMap*>(gameObjects[0])->getRows())
	{
		ny = 0;
	}
	if (static_cast<GameMap*>(gameObjects[0])->cells[ny][nx] != Wall)
	{
		return true;
	}
	else return false;
}
int PlayState::getPacmanLives()//Devuelve las vidas del Pacman
{
	return static_cast<Pacman*>(gameObjects[gameObjects.size() - 1])->getLives();
}
void PlayState::vulnerabilityOff()
{

	for (int i = 1; i < gameObjects.size() - 1; i++)
	{
		static_cast<Ghost*>(gameObjects[i])->vulnerabilityOn();
	}
}

vector<int> PlayState::sghostCounter()//Enumera y almacena los SmartGhost fétiles
{

	vector<int> ghost(0);
	for (int i = 1; i < gameObjects.size() - 1; i++)
	{
		if (typeid(*gameObjects[i]) == typeid(SmartGhost))
		{
			if (static_cast<SmartGhost*>(gameObjects[i])->getFertil())
			{
				ghost.push_back(i);
			}
		}
	}
	return ghost;
}

void PlayState::handleBirths()//Comprueba si se han cruzado dos SmartGhost fétiles y crea el nuevo
{
	vector<int> ghost = sghostCounter();
	bool posFind = false;;
	int x, y;
	if (ghost.size() >= 2)
	{
		for (int i = 0; i < ghost.size() - 1; i++)
		{
			for (int j = i + 1; j < ghost.size(); j++)
			{
				if (static_cast<Ghost*>(gameObjects[ghost[i]])->getPosX() == static_cast<Ghost*>(gameObjects[ghost[j]])->getPosX() &&
					static_cast<Ghost*>(gameObjects[ghost[i]])->getPosY() == static_cast<Ghost*>(gameObjects[ghost[j]])->getPosY())
				{
					x = static_cast<Ghost*>(gameObjects[ghost[i]])->getPosX();
					y = static_cast<Ghost*>(gameObjects[ghost[i]])->getPosY();
					if (static_cast<GameMap*>(gameObjects[0])->cells[y + 1][x] != Wall)
					{
						y = y + 1;
						posFind = true;

					}
					else if (static_cast<GameMap*>(gameObjects[0])->cells[y - 1][x] != Wall)
					{
						y = y - 1;
						posFind = true;
					}
					else if (static_cast<GameMap*>(gameObjects[0])->cells[y][x + 1] != Wall)
					{
						x = x + 1;
						posFind = true;
					}
					else if (static_cast<GameMap*>(gameObjects[0])->cells[y][x - 1] != Wall)
					{
						x = x - 1;
						posFind = true;
					}
					if (posFind){
						SmartGhost* sg = new SmartGhost(game,this, x, y);
						gameObjects.push_back(gameObjects[gameObjects.size() - 1]);
						gameObjects[gameObjects.size() - 2] = sg;
						static_cast<SmartGhost*>(gameObjects[ghost[i]])->fertilOff();
						static_cast<SmartGhost*>(gameObjects[ghost[j]])->fertilOff();

					}
				}
			}
		}
	}
}

int PlayState::pacmanColl()//Comprueba si algun fantasma ha colisionado con el Pacman
{
	int i = 1;
	while (i < gameObjects.size() - 1)
	{
		if (static_cast<Ghost*>(gameObjects[i])->getPosX() == static_cast<Pacman*>(gameObjects[gameObjects.size() - 1])->getPosX() &&
			static_cast<Ghost*>(gameObjects[i])->getPosY() == static_cast<Pacman*>(gameObjects[gameObjects.size() - 1])->getPosY())
		{
			return i;
		}
		i++;
	}
	return 0;
}

void PlayState::handleCollision(){//Gestiona las colisiones entre Pacman y los fantasmas
	int coll = pacmanColl();
	if (coll != 0)
	{

		if (!static_cast<Ghost*>(gameObjects[coll])->getVulnerability())//Si el fantasma en cuestión es invulnerable, Pacman pierde una vida
		{
			static_cast<Pacman*>(gameObjects[gameObjects.size() - 1])->die();
			render();
			SDL_Delay(500);
			resetPositions();
		}
		else
		{
			if (static_cast<SmartGhost*>(gameObjects[coll])->dead()){
				gameObjects.erase(gameObjects.begin() + coll);

			}
			else {
				static_cast<GameCharacter*>(gameObjects[coll])->backToIni();
				static_cast<Ghost*>(gameObjects[coll])->vulnerabilityOff();
			}
			addScore(100);
		}
	}
}

void PlayState::resetPositions(){//Reinicia las posiciones de los fantasmas y el pacman
	for (int i = 1; i < gameObjects.size(); i++)
	{
		static_cast<GameCharacter*>(gameObjects[i])->backToIni();
	}
}

void PlayState::checkEndGame(){//Comprueba que no quedan comidas ni vitaminas en el mapa
	if (static_cast<GameMap*>(gameObjects[0])->getFoods() + static_cast<GameMap*>(gameObjects[0])->getVitamins() == 0){
		gameWon();
	}
}
void PlayState::gameOver(){//Termina el juego cuando has perdido
	game->endScreen(false);
}
void PlayState::gameWon(){//Termina el juego cuando ganas
	
	level++;
	if (level <= 5){
		userinterface->nextLevelRender();
		SDL_Delay(1500);
		nextLevel();
	}
	else
	{
		game->endScreen(true);
	}
		
}

void PlayState::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN){
		if (e.key.keysym.sym == SDLK_DOWN){
			static_cast<Pacman*>(gameObjects[gameObjects.size() - 1])->changeDir('d');
		}
		else if (e.key.keysym.sym == SDLK_UP){
			static_cast<Pacman*>(gameObjects[gameObjects.size() - 1])->changeDir('u');
		}
		else if (e.key.keysym.sym == SDLK_RIGHT){
			static_cast<Pacman*>(gameObjects[gameObjects.size() - 1])->changeDir('r');
		}
		else if (e.key.keysym.sym == SDLK_LEFT){
			static_cast<Pacman*>(gameObjects[gameObjects.size() - 1])->changeDir('l');
		}
		else if (e.key.keysym.sym == SDLK_s)
		{
			game->pause();
		}
	}
}