#include "Game.h"
#include <fstream>


Game::Game()
{
	winX = winY = 50;
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	window = SDL_CreateWindow("Pacman", winX, winY, winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	//gamemap = new GameMap(20, 20);//Valor de prueba 20x20

	if (renderer == nullptr)//Si hay errores activa el flag
	{
		error = true;
	}
	else
	{
		//stateMachine = new GameStateMachine();
		stateMachine = new GameStateMachine();
		MainMenuState* mm = new MainMenuState(this);
		stateMachine->pushState(mm);

	}
}
Game::~Game()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

}

int Game::getWinW(){//Pide el ancho de la ventana
	return winWidth;
}
int Game::getWinH(){//Pide la altura de la altura
	return winHeight;
}
void Game::handleEvents()//Comprueba eventos
{
	while (SDL_PollEvent(&event) && !exit) {

		if (event.type == SDL_QUIT)
		{
			exit = true;
			//exitlevel = true;
		}

		else
		{
			stateMachine->currentState()->handleEvent(event);
		}
	}
}
void Game::playState()
{
	PlayState* ps = new PlayState(this);
	stateMachine->pushState(ps);

}
void Game::playLoad(string filename)
{
	PlayState* ps = new PlayState(this,filename);
	stateMachine->pushState(ps);
}
void Game::pause()
{
	PauseState* ps = new PauseState(this);
	stateMachine->pushState(ps);
}
void Game::resume()
{
	GameState* ps = stateMachine->popState();
	delete ps;
}
void Game::saveResume(string filename)
{
	GameState* ps = stateMachine->popState();
	delete ps;
	GameState* pls = stateMachine->currentState();
	dynamic_cast<PlayState*>(pls)->saveGame(filename);
}
void Game::endScreen(bool win)
{
	EndState* es = new EndState(this, win);
	stateMachine->pushState(es);
}

void Game::quitEndScreen()
{
	GameState* es = stateMachine->popState();
	delete es;
	GameState* ps = stateMachine->popState();
	delete ps;

}

void Game::render(){//Aplica el render del mapa, de las vidas, y de las entidades
	SDL_RenderClear(renderer);
	stateMachine->currentState()->render();
	SDL_RenderPresent(renderer);
}
void Game::run()//Controla el bucle del juego
	{
		while (!exit){
			handleEvents();
			stateMachine->currentState()->update();
			render();
			SDL_Delay(150);
		}
	}