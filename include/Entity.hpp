#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Math.hpp"
#include "utils.hpp"
#include <vector>

class Entity{
public:
	Entity(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_size);
	Vector2f& getPos(){
		return pos;
	}
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
	const SDL_Rect getConstFrame();
	void moveRight(int move){
		pos.x += move;
	}
	void moveLeft(int move){
		pos.x -= move;
	}
	void moveUp(int move){
		pos.y -= move;
	}
	void moveDown(int move){
		pos.y += move;
	}
	void setPos(Vector2f p_pos){
		pos = p_pos;
	}
	void setxPos(float p_x){
		pos.x = p_x;
	}
	void setyPos(float p_y){
		pos.y = p_y;
	}
	float getxPos(){
		return pos.x;
	}
	float getyPos(){
		return pos.y;
	}
	void jump(bool& firstJump, Vector2f& pos0, Vector2f& speed, Vector2f& speed0, float& t0, Entity& knight, float& t, 
	bool& collisionBottom, bool& isJumping, const int move, const bool direction, bool& jumping, const int bottom, std::vector<std::pair<size_t, size_t>>& current,
	std::vector<std::pair<size_t, size_t>>& run, std::vector<std::pair<size_t, size_t>>& idle1, const float g, Entity collisionBox);
	Vector2f pos;
	SDL_Texture* tex;
	Vector2f size;
	SDL_Rect currentFrame;
	float velocityY = 0.f;
};