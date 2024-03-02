#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Entity.hpp"

class RenderWindow 
{
public:
	RenderWindow(const char* p_title, int p_w, int p_h);
	SDL_Texture* loadTexture(const char* p_filePath);
	int getRefreshRate();
	void cleanUp();
	void clear();
	void render(Entity& p_entity, float factor_pos, float factor_w, float factor_h);
	void renderSprite(Entity& p_entity, float factor_pos, float factor_w, float factor_h, Vector2f sprite_pos, Vector2f sprite_size);
	void display();
	SDL_Renderer* getRenderer(){
		return renderer;
	}
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};