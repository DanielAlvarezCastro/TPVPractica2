#include "MenuButton.h"
#include "Game.h"


MenuButton::MenuButton(Game* g, Texture* t,SDL_Rect r, CallBackOnClick* cb) : GameObject(g)
{
	texture = t;
	rect = r;
	callback = cb;
}


MenuButton::~MenuButton()
{
}

void MenuButton::render()
{
	texture->render(game->renderer, rect);
}

void MenuButton::handleEvent(SDL_Event& e)
{
	SDL_GetMouseState(&mouse.x, &mouse.y);
	if (SDL_PointInRect(&mouse, &rect))
	{
		callback(game);
	}
}
