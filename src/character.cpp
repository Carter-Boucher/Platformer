#include "character.hpp"

character::character(){

}

character::character(float health, std::vector<int> damage){

}

bool character::heal(float p_health){
	if(health > 0) {
		health += p_health;
		return true;
	}
	else{
		return false;
	}
}

bool character::takeDamage(float p_health){
	if(health - p_health < 0) {
		dead = true;
		return false;
	}
	health -= p_health;
	return true;
}
