#include "Entity.hpp"

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_size)
:pos(p_pos), tex(p_tex), size(p_size)
{
	//std::cout << p_size.x << " " << p_size.y << std::endl;
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = p_size.x;
	currentFrame.h = p_size.y;
}

SDL_Texture* Entity::getTex(){
	return tex;
}

SDL_Rect Entity::getCurrentFrame(){
	return currentFrame;
}

const SDL_Rect Entity::getConstFrame(){
	return currentFrame;
}

void Entity::jump(bool& firstJump, Vector2f& pos0, Vector2f& speed, Vector2f& speed0, float& t0, Entity& knight, float& t, 
	bool& collisionBottom, bool& isJumping, const int move, const bool direction, bool& jumping, const int bottom, std::vector<std::pair<size_t, size_t>>& current, std::vector<std::pair<size_t, size_t>>& run, std::vector<std::pair<size_t, size_t>>& idle1, const float g, Entity collisionBox){
	int speedJump = 1500;
	if(firstJump){
		t0=utils::hireTimeInSeconds();
		pos0=pos;
		speed0 = speed;
		speed0.y += speedJump;
		speed0.x += speedJump/3;
		isJumping = true;
		firstJump = false;
		jumping = true;
	}
	if(isJumping)
	{
	    t = utils::hireTimeInSeconds() - t0;
	    //printf("pos: %f, speed: %f, t: %f, g: %f    answer: %f \r", pos0.y, speed0.y, t, g, pos0.y + (speed0.y * t - g * t) * t);
	    if( (g * 175 * t * t) > 570) current = { {3, 1}, {3, 2} };
	    knight.setyPos(pos0.y - (speed0.y * t - g * 175 * t * t));
		if(move == 1) {
			knight.setxPos(knight.getxPos() + speed0.x*t/50);
		}
	    if(move == 0) {
	    	knight.setxPos(knight.getxPos() - speed0.x*t/50);
	    }
	    // printf("%f, %f 		\r\r", pos0.x, speed0.x*t);
	    // std::cout << pos0.x << ", " << speed0.x*t << "		\r\r";
	    this->prevMove = move;
	    // test that the character is not on the ground again.
	    if(collisionBox.getyPos() + 192 > 630)
	    {
	    	this->prevMove = -2;
	    	jumping = false;
	    	//std::cout << "here";
	        knight.setyPos((int)(627-192));
	        collisionBottom = false;
	        isJumping = false;
	        firstJump = false;
	        if(move == 0 || move == 1 || move == 2 || move == 3) current = run;
	        else{current = idle1;}
	        SDL_Delay(25);
	    }
	}
	
	return;
}
