#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == NULL)
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

	return texture;
}

int RenderWindow::getRefreshRate(){
	int displayIndex = SDL_GetWindowDisplayIndex(window);
	SDL_DisplayMode mode;
	SDL_GetDisplayMode(displayIndex, 0, &mode);
	return mode.refresh_rate;
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& p_entity, float factor_pos, float factor_w, float factor_h)
{
	SDL_Rect src;
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;
	//std::cout << p_entity.getCurrentFrame().w << " " << p_entity.getCurrentFrame().h << std::endl;

	SDL_Rect dst;
	dst.x = p_entity.getPos().x * factor_pos;
	dst.y = p_entity.getPos().y * factor_pos;
	dst.w = p_entity.getCurrentFrame().w * factor_w;
	dst.h = p_entity.getCurrentFrame().h * factor_h;

	SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
}


//vector2f sprite size, vector2f sprite position
void RenderWindow::renderSprite(Entity& p_entity, float factor_pos, float factor_w, float factor_h, Vector2f sprite_pos, Vector2f sprite_size)
{
	SDL_Rect src;
	src.x = sprite_pos.x;
	src.y = sprite_pos.y;
	src.w = sprite_size.x;
	src.h = sprite_size.y;
	//std::cout << p_entity.getCurrentFrame().w << " " << p_entity.getCurrentFrame().h << std::endl;

	SDL_Rect dst;
	dst.x = p_entity.getPos().x * factor_pos;
	dst.y = p_entity.getPos().y * factor_pos;
	dst.w = p_entity.getCurrentFrame().w * factor_w;
	dst.h = p_entity.getCurrentFrame().h * factor_h;

	SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
}

void RenderWindow::renderFlip(Entity& p_entity, float factor_pos, float factor_w, float factor_h, Vector2f sprite_pos, Vector2f sprite_size, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	SDL_Rect src;
	src.x = sprite_pos.x;
	src.y = sprite_pos.y;
	src.w = sprite_size.x;
	src.h = sprite_size.y;
	//std::cout << p_entity.getCurrentFrame().w << " " << p_entity.getCurrentFrame().h << std::endl;

	SDL_Rect dst;
	dst.x = p_entity.getPos().x * factor_pos;
	dst.y = p_entity.getPos().y * factor_pos;
	dst.w = p_entity.getCurrentFrame().w * factor_w;
	dst.h = p_entity.getCurrentFrame().h * factor_h;

    SDL_RenderCopyEx( renderer, p_entity.getTex(), &src, &dst, angle, center, flip );
}



void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}

