#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Math.hpp"

class Entity{
public:
	Entity(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_size);
	Vector2f& getPos(){
		return pos;
	}
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
	void moveRight(){
		pos.x += 10;
	}
	void moveLeft(){
		pos.x -= 10;
	}
	void setPos(Vector2f p_pos){
		pos = p_pos;
	}
private:
	Vector2f pos;
	Vector2f size;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};