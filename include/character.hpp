#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Entity.hpp"

class character{
public:
	character();
	character(float health, std::vector<int> damage);
	bool heal(float p_health);
	bool takeDamage(float p_health);

	void setHealth(float p_health){ health = p_health;}
	void setDamage(std::vector<int> p_damage){ damage = p_damage;}
	void addDamageSource(int p_damageValue) { damage.push_back(p_damageValue);}

	float getHealth(){return health;}
	std::vector<int> getDamage(){ return damage;}
	int getDamageSource(int p_at){ if(p_at<(int)damage.size()) return damage.at(p_at);}
private:
	float health;
	std::vector<int> damage;
	bool dead;
};