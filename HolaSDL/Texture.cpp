#include "Texture.h"

Texture::Texture()
{
}
Texture::~Texture()
{
	free();
}

void Texture::free()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
	w = h = 0;
}
bool Texture::load(SDL_Renderer* renderer, string filename, uint numRows, uint numCols){//Carga la textura a parti de un archivo

	SDL_Surface* surface = IMG_Load(filename.c_str());
	if (surface == nullptr){
		string t = IMG_GetError();
		throw SDLError("Error de cargado de textura-> ", t);
	}
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == nullptr)	{
		string t = SDL_GetError();
		throw SDLError("Error de cargado de textura-> ", t);
	}
	SDL_RenderCopy(renderer, texture, nullptr, nullptr);
	h = surface->h;
	w = surface->w;
	fw = w / numCols;
	fh = h / numRows;
	SDL_FreeSurface(surface);
	return true;
}
void Texture::render(SDL_Renderer* renderer, const SDL_Rect& destRect, SDL_RendererFlip flip){//Copia la textura al render
	SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}
void Texture::renderFrame(SDL_Renderer* renderer, SDL_Rect& srcRect, const SDL_Rect& destRect, int row, int col, SDL_RendererFlip flip){//Pinta un frame determinado
	srcRect.x = fw*(col);//El rectángulo fuente se posiciona según la columna
	srcRect.y = fh*(row);
	srcRect.w = fw;
	srcRect.h = fh;
	SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}
bool Texture::loadFromText(SDL_Renderer*renderer, string text,const	Font* font,SDL_Color color)	{
	SDL_Surface* textSurface = font->generateSurface(text, color);
	if (textSurface == nullptr){
		string t = TTF_GetError();
		throw SDLError("Error de cargado de fuente-> ", t);
		/*cout << "Unable	to	render	text	surface!	SDL_ttf	Error:	"
		<< TTF_GetError() << "\n";*/
	}
	else	
	{
		free();
		texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (texture == nullptr)	{
			string t = SDL_GetError();
			throw SDLError("Error de cargado de fuente-> ", t);
			/*cout << "Unable	to	create	texture	from	text!	SDL	Error:	"
				<< SDL_GetError() << "\n";
			w = h = 0;*/
		}
		else	{
			w = textSurface->w;
			h = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
	return	texture != nullptr;
}