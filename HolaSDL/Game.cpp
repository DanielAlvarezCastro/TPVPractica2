#include "Game.h"
#include <fstream>


Game::Game()
{
	level = 1;
	score = 0;
	winX = winY = 50;
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	window = SDL_CreateWindow("Pacman", winX, winY, winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	//gamemap = new GameMap(20, 20);//Valor de prueba 20x20
	userinterface = new UserInterface(this);

	if (renderer == nullptr)//Si hay errores activa el flag
	{
		error = true;
	}
	else
	{
		//Inicializa Textura del SpriteSheet
		pacmanText = new Texture();
		//Lo carga
		pacmanText->load(renderer, "..\\images\\characters1.png", 4, 14);
		screenFont= new Font("..\\fonts\\Kiloton v1.0.ttf", 50);
		white.a = 255;
		//Inicializa Texturas de Interfaz
		scoreText = new Texture();
		saveCode = new Texture();
		saveText = new Texture();
		savePanel = new Texture();
		scoreText->loadFromText(renderer, "Score:    ", screenFont, white);
		savePanel->load(renderer, "..\\images\\bluePanel.png", 1, 1);
		saveText->loadFromText(renderer, "Create save code", screenFont, white);

		white.g = 255;
		white.b = 255;
		white.r = 255;
		scorePos.h = 27;
		spanelPos.h = 200;
		stextPos.h = 50;
		scodePos.h = 100;

		scorePos.w = 100;
		spanelPos.w = 400;
		stextPos.w = 200;
		scodePos.w = 300;

		scorePos.x = 350;
		scodePos.x = 270;
		spanelPos.x = 250;
		stextPos.x=270 ;
		
		spanelPos.y = 200;
		stextPos.y = 220;
		scodePos.y = 300;
		scorePos.y = 579;


	}
}
Game::~Game()
{
	//Borra el SpriteSheet
	delete pacmanText;


	delete userinterface;

	delete scoreText;
	delete savePanel;
	delete saveText;
	delete saveCode;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

}

int Game::getRows()//Pide las filas
{
	return static_cast<GameMap*>(gameObjects[0])->getRows();
}
int Game::getCols()//Pide las columnas
{
	return static_cast<GameMap*>(gameObjects[0])->getCols();
}
int Game::getWinW(){//Pide el ancho de la ventana
	return winWidth;
}
int Game::getWinH(){//Pide la altura de la altura
	return winHeight;
}
MapCell Game::getCell(int x, int y)//Devuelve el valor que hay en una celda
{
	return static_cast<GameMap*>(gameObjects[0])->cells[y][x];//La representación en la celda es al contrario
}

void Game::changeCell(int x, int y, MapCell cell)//Cambia el valor de una celda, se usa en el pacman al comer una vitamina o comida y cambiarla por empty
{
	static_cast<GameMap*>(gameObjects[0])->cells[y][x] = cell;
}
void Game::substractFood()//Resta 1 al contador de comida
{
	addScore(10);
	static_cast<GameMap*>(gameObjects[0])->foods--;
}
void Game::substractVitamin()//Resta 1 al contador de vitamina
{
	addScore(50);
	static_cast<GameMap*>(gameObjects[0])->vitamins--;
}

void Game::menuEvents()//Comprueba eventos del menú
{
	while (SDL_PollEvent(&event) && !exitMenu) {
		if (event.type == SDL_QUIT)//Si cierra la ventana termina el juego directamente
		{
			exitMenu = true;
			exit = true;
		}
		else if (event.type == SDL_KEYDOWN){
			if (event.key.keysym.sym != NULL){
				exitMenu = true;
			}
		}
	}
}
void Game::nextLevel(){//Controla el nivel que se va a cargar 
	exitlevel = false;
	if (level == 1){
		loadLevel("level01");
		//loadSave("555");//Carga el nivel actual
		userinterface->setLifeSize();//Ajusta los valores de la interfaz de vida
	}
	else if (level == 2){
		loadLevel("level02");
		userinterface->setLifeSize();
	}
	else if (level == 3){
		loadLevel("level03");
		userinterface->setLifeSize();
	}
	else if (level == 4){
		loadLevel("level04");
		userinterface->setLifeSize();
	}
	else if (level == 5){
		loadLevel("level05");
		userinterface->setLifeSize();
	}
	else exit = true;
	//SDL_PointInRect()
}
void Game::loadSave(string filename)
{
	ifstream archivo;
	gameObjects.clear();
	archivo.open("..\\saves\\" + filename + ".pac");
	archivo >> level;
	archivo >> score;
	createMap(archivo);
}

void Game::loadLevel(string filename)
{
	ifstream archivo;
	gameObjects.clear();
	archivo.open("..\\levels\\" + filename + ".pac");
	createMap(archivo);
}
void Game::createMap(ifstream& archivo)//Lee de un archivo y crea la matriz del mapa
{
	int dato;
	GameMap* gm = new GameMap(this);
	gm->loadFromFile(archivo);
	int size;
	archivo >> size;
	size= size;
	gameObjects.push_back(gm);
	for (int i = 1; i <= size; i++)
	{
		archivo >> dato;
		if (dato == 1)
		{
			SmartGhost* sg = new SmartGhost(this);			
			gameObjects.push_back(sg);
			gameObjects[i]->loadFromFile(archivo);
		}
		else
		{
			Ghost* g = new Ghost(this);
			gameObjects.push_back(g);
			gameObjects[i]->loadFromFile(archivo);
		}
	}
	p = new Pacman(this);
	gameObjects.push_back(p);
	gameObjects[gameObjects.size()- 1]->loadFromFile(archivo);
	archivo.close();

}


void Game::handleEvents()//Comprueba eventos
{
	while (SDL_PollEvent(&event) && !exit) {
		
		if (event.type == SDL_QUIT)
		{
			exit = true;
			exitlevel = true;
		}
		else if (event.type == SDL_KEYDOWN && !saving){
			if (event.key.keysym.sym == SDLK_DOWN){
				static_cast<Pacman*>(gameObjects[gameObjects.size()-1])->changeDir('d');
			}
			else if (event.key.keysym.sym == SDLK_UP){
				static_cast<Pacman*>(gameObjects[gameObjects.size() - 1])->changeDir('u');
			}
			else if (event.key.keysym.sym == SDLK_RIGHT){
				static_cast<Pacman*>(gameObjects[gameObjects.size() - 1])->changeDir('r');
			}
			else if (event.key.keysym.sym == SDLK_LEFT){
				static_cast<Pacman*>(gameObjects[gameObjects.size() - 1])->changeDir('l');
			}
			else if (event.key.keysym.sym == SDLK_s)
			{
				saving = true;
			}
		}
		else if (event.type == SDL_KEYDOWN && saving)
			{
				if (event.key.keysym.sym == SDLK_0){
					codeN += "0";
					saveCode->loadFromText(renderer, codeN, screenFont, white);
				}
				else if (event.key.keysym.sym == SDLK_1){
					codeN += "1";
					saveCode->loadFromText(renderer, codeN, screenFont, white);
				}
				else if (event.key.keysym.sym == SDLK_2){
					codeN += "2";
					saveCode->loadFromText(renderer, codeN, screenFont, white);
				}
				else if (event.key.keysym.sym == SDLK_3){
					codeN += "3";
					saveCode->loadFromText(renderer, codeN, screenFont, white);
				}
				else if (event.key.keysym.sym == SDLK_4){
					codeN += "4";
					saveCode->loadFromText(renderer, codeN, screenFont, white);
				}
				else if (event.key.keysym.sym == SDLK_5){
					codeN += "5";
					saveCode->loadFromText(renderer, codeN, screenFont, white);
				}
				else if (event.key.keysym.sym == SDLK_6){
					codeN += "6";
					saveCode->loadFromText(renderer, codeN, screenFont, white);
				}
				else if (event.key.keysym.sym == SDLK_7){
					codeN += "7";
					saveCode->loadFromText(renderer, codeN, screenFont, white);
				}
				else if (event.key.keysym.sym == SDLK_8){
					codeN += "8";
					saveCode->loadFromText(renderer, codeN, screenFont, white);
				}
				else if (event.key.keysym.sym == SDLK_9){
					codeN += "9";
					saveCode->loadFromText(renderer, codeN, screenFont, white);
				}
				else if (event.key.keysym.sym == SDLK_RETURN)
				{
					saving = false;
					ofstream archivo("..\\saves\\"+codeN + ".pac");
					archivo << level << " " << score << endl;
					gameObjects[0]->saveToFile(archivo);
					archivo << endl;
					archivo << gameObjects.size() - 2;
					archivo << endl;
					for (int i = 1; i < gameObjects.size(); i++)
					{
						gameObjects[i]->saveToFile(archivo);
						archivo << endl;
					}
					codeN = "";
				}
				
			}
	}
}

void Game::addScore(int cuantity)
{
	score += cuantity;
	string scoreSTR = "Score:" + to_string(score)+ " ";

	scoreText->loadFromText(renderer, scoreSTR, screenFont, white);
}
void Game::update(){//Controla los updates de las entidades y comprueba si ha habido una colisión
	for (int i = gameObjects.size()-1; i >=0; i--)
	{
		gameObjects[i]->update();
		if (i == gameObjects.size() - 1)
		{
		handleCollision();
		}
	}

	handleCollision();
	checkEndGame();
}
void Game::render(){//Aplica el render del mapa, de las vidas, y de las entidades
	SDL_RenderClear(renderer);
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->render();
	}
	gameObjects[gameObjects.size()-1]->render();

	scoreText->render(renderer, scorePos);
	userinterface->renderLives();
	if (saving)
	{
		savePanel->render(renderer, spanelPos);
		saveText->render(renderer, stextPos);
		saveCode->render(renderer, scodePos);
	}
	SDL_RenderPresent(renderer);
}
void Game::run(){//Controla el bucle del juego
	userinterface->menuRender();//Pinta la página principal
	while (!exitMenu){//Este bucle controla la pulsación del menú
		menuEvents();
	}
	while (level < 6 && !exit){//Este bucle controla que no se salga o se haya superado el nivel máximo
		nextLevel();//Selecciona el siguiente nivel (Empieza en 1)
		SDL_Delay(1000);
		while (!exitlevel){//Bucle de la pantalla de juego
				handleEvents();
			if (!saving){
				update();
			}
			render();
			SDL_Delay(150);
		}

		//delete gamemap;//Borra el gamemap actual
		if (gameover){//Si se activa el flag de game over se pinta la pantalla y posteriormente se sale del bucle
			userinterface->gameOverRender();
		}
		else if (!exit){
			if (level < 6){//Si todavía hay niveles restantes se activa la pantalla de siguiente nivel en lo que se carga el mapa
				userinterface->nextLevelRender();
			}
			else{
				userinterface->gameWonRender();//Si llegas al nivel máximo has superado el juego				
			}
		}
		SDL_Delay(1000);
	}
}

bool Game::nextCell(int x, int y, int dirX, int dirY, int& nx, int& ny)//Si la siguiente posición es una pared devuelve false
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
int Game::getPacmanLives()
{
	return static_cast<Pacman*>(gameObjects[gameObjects.size()-1])->getLives();
}
void Game::vulnerabilityOff()
{
	for (int i = 1; i < gameObjects.size() - 1; i++)
	{
		static_cast<Ghost*>(gameObjects[i])->vulnerabilityOn();
	}
}
int Game::pacmanColl()
{
	int i = 1;
	while(i < gameObjects.size()- 1)
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
void Game::handleCollision(){//Gestiona las colisiones entre Pacman y los fantasmas
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
			static_cast<GameCharacter*>(gameObjects[coll])->backToIni();
			static_cast<Ghost*>(gameObjects[coll])->vulnerabilityOff();
			addScore(100);
		}
	}
}

void Game::resetPositions(){//Reinicia las posiciones de los fantasmas y el pacman
	for (int i = 1; i < gameObjects.size(); i++)
	{
		static_cast<GameCharacter*>(gameObjects[i])->backToIni();
	}
}

void Game::checkEndGame(){//Comprueba que no quedan comidas ni vitaminas en el mapa
	if (static_cast<GameMap*>(gameObjects[0])->getFoods() + static_cast<GameMap*>(gameObjects[0])->getVitamins() == 0){
		gameWon();
	}
}
void Game::gameOver(){//Termina el juego cuando has perdido
	gameover = true;
	exit = true;
	exitlevel = true;
}
void Game::gameWon(){//Termina el juego cuando ganas
	exitlevel = true;
	level++;
}


