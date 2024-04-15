#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <random>
#include <map>

// #include <random>current[event.key.keysym.sym] = true;
// #include <iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Math.hpp"
#include "utils.hpp"
#include "CollisionBox.hpp"
#include "CollisionPlane.hpp"
#include "character.hpp"

float getMoveSpeed(int refreshRate);
#define TICK_INTERVAL    15

static Uint32 next_time;

Uint32 time_left(void)
{
    Uint32 now;

    now = SDL_GetTicks();
    if(next_time <= now)
        return 0;
    else
        return next_time - now;
}

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0) {std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;}

	if (!(IMG_Init(IMG_INIT_PNG))) {std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;}

	RenderWindow window("GAME v1.0", SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_Texture* collisionBoxText = window.loadTexture("res/gfx/collisionBox.png");
	Entity collisionBox(Vector2f(0,0), collisionBoxText, Vector2f(1100,1100));

	//grass ground
	SDL_Texture* grassTexture = window.loadTexture("res/gfx/ground_grass_1.png");
	std::vector<Entity> grassEntities = {Entity(Vector2f(0, 156), grassTexture, Vector2f(32,32)),Entity(Vector2f(30, 156), grassTexture, Vector2f(32,32)),Entity(Vector2f(60, 156), grassTexture, Vector2f(32,32)),Entity(Vector2f(90, 156), grassTexture, Vector2f(32,32)),Entity(Vector2f(120, 156), grassTexture, Vector2f(32,32)),Entity(Vector2f(150, 156), grassTexture, Vector2f(32,32)),Entity(Vector2f(180, 156), grassTexture, Vector2f(32,32)),Entity(Vector2f(210, 156), grassTexture, Vector2f(32,32)),Entity(Vector2f(240, 156), grassTexture, Vector2f(32,32)),Entity(Vector2f(270, 156), grassTexture, Vector2f(32,32)),Entity(Vector2f(300, 156), grassTexture, Vector2f(32,32))};
	//blue sky			
	SDL_Texture* skyTexture = window.loadTexture("res/gfx/sky.png");
	Entity sky(Vector2f(0, 0), skyTexture, Vector2f(735,414));

	//beach
	SDL_Texture* beachSkyTexture = window.loadTexture("res/gfx/sunset.png");
	Entity beachSky(Vector2f(0, 0), beachSkyTexture, Vector2f(600,400));
	//500x500
	SDL_Texture* beachGroundTexture = window.loadTexture("res/gfx/sand.png");
	std::vector<Entity> beachEntities = {Entity(Vector2f(0, 156), beachGroundTexture, Vector2f(500,500)),Entity(Vector2f(30, 156), beachGroundTexture, Vector2f(500,500)),Entity(Vector2f(60, 156), beachGroundTexture, Vector2f(500,500)),Entity(Vector2f(90, 156), beachGroundTexture, Vector2f(500,500)),Entity(Vector2f(120, 156), beachGroundTexture, Vector2f(500,500)),Entity(Vector2f(150, 156), beachGroundTexture, Vector2f(500,500)),Entity(Vector2f(180, 156), beachGroundTexture, Vector2f(500,500)),Entity(Vector2f(210, 156), beachGroundTexture, Vector2f(500,500)),Entity(Vector2f(240, 156), beachGroundTexture, Vector2f(500,500)),Entity(Vector2f(270, 156), beachGroundTexture, Vector2f(500,500)),Entity(Vector2f(300, 156), beachGroundTexture, Vector2f(500,500))};

	//hell
	SDL_Texture* hellSkyTexture = window.loadTexture("res/gfx/hell.png");
	Entity hellSky(Vector2f(0, 0), hellSkyTexture, Vector2f(850,850));
	//1350x860
	SDL_Texture* hellGroundTexture = window.loadTexture("res/gfx/rock.png");
	std::vector<Entity> hellEntities = {Entity(Vector2f(0, 156), hellGroundTexture, Vector2f(1450,860)),Entity(Vector2f(50, 156), hellGroundTexture, Vector2f(1450,860)),Entity(Vector2f(100, 156), hellGroundTexture, Vector2f(1450,860)),Entity(Vector2f(150, 156), hellGroundTexture, Vector2f(1450,860)),Entity(Vector2f(200, 156), hellGroundTexture, Vector2f(1450,860)),Entity(Vector2f(250, 156), hellGroundTexture, Vector2f(1450,860)),Entity(Vector2f(300, 156), hellGroundTexture, Vector2f(1450,860)),Entity(Vector2f(350, 156), hellGroundTexture, Vector2f(1450,860)),Entity(Vector2f(400, 156), hellGroundTexture, Vector2f(1450,860))};

	//sprites are 50x37, 350x407
	SDL_Texture* kinghtTexture = window.loadTexture("res/gfx/adventurer-sheet.png");
	Entity knight(Vector2f(390, 408), kinghtTexture, Vector2f(350,407));
	std::vector<std::pair<size_t, size_t>> idle1  { {0, 0}, {0, 1}, {0, 2}, {0, 3} };
	std::vector<std::pair<size_t, size_t>> crouch { {0, 4}, {0, 5}, {0, 6}, {1, 0} };
	std::vector<std::pair<size_t, size_t>> run    { {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6} };
	std::vector<std::pair<size_t, size_t>> jump   { {2, 0}, {2, 1}, {2, 2}, {2, 3} };
	std::vector<std::pair<size_t, size_t>> mid    { {2, 4}, {2, 5}, {2, 6}, {3, 0} };
	std::vector<std::pair<size_t, size_t>> fall   { {3, 1}, {3, 2} };
	std::vector<std::pair<size_t, size_t>> slide  { {3, 3}, {3, 4}, {3, 5}, {3, 6}, {4, 0} };
	std::vector<std::pair<size_t, size_t>> grab   { {4, 1}, {4, 2}, {4, 3}, {4, 4}};
	std::vector<std::pair<size_t, size_t>> climb  { {4, 5}, {4, 6}, {5, 0}, {5, 1}, {5, 2} };
	std::vector<std::pair<size_t, size_t>> idle2  { {5, 3}, {5, 4}, {5, 5}, {5, 6} };
	std::vector<std::pair<size_t, size_t>> attack1{ {6, 0}, {6, 1}, {6, 2}, {6, 3}, {6, 4} };
	std::vector<std::pair<size_t, size_t>> attack2{ {6, 5}, {6, 6}, {7, 0}, {7, 1}, {7, 2}, {7, 3} };
	std::vector<std::pair<size_t, size_t>> attack3{ {7, 4}, {7, 5}, {7, 6}, {8, 0}, {8, 1}, {8, 2} };
	std::vector<std::pair<size_t, size_t>> hurt   { {8, 3}, {8, 4}, {8, 5} };
	std::vector<std::pair<size_t, size_t>> die    { {8, 6}, {9, 0}, {9, 1}, {9, 2}, {9, 3}, {9, 4}, {9, 5} };
	std::vector<std::pair<size_t, size_t>> jump2  { {9, 6}, {10, 0}, {10, 1} };
	std::vector<std::pair<size_t, size_t>> current = idle1;

	SDL_Texture* gameOverTextTex = window.loadTexture("res/gfx/game_over.png");
	Entity gameOverText(Vector2f(700, 100), gameOverTextTex, Vector2f(1080,1080));

	SDL_Texture* enemyText = window.loadTexture("res/gfx/enemy (1).png");
	Entity enemy(Vector2f(0, 0), enemyText, Vector2f(715, 349));
	std::vector< size_t > enemyMove { 0, 1, 2 };

	SDL_Texture* healthBarText = window.loadTexture("res/gfx/healthbar (1).png");
	Entity healthbar(Vector2f(100, 500), healthBarText, Vector2f(457,431));
	std::vector< size_t > healthbarMove { 0, 1, 2, 3, 4 };


	SDL_Event event;
	float accumulator = 0.f, currentXAnimation = 0.f, currentYAnimation = 0.f, currentTime = utils::hireTimeInSeconds(), t0 = 0.f, t = 0.f, degrees = 0.f, t1 = 0.f;
	int index = 0, deathCounter = 0, currentBack = 0, move = -1, spriteAnimate = 0, left = 0, right = 0, top = 0, bottom = 0, 
		prevLeft = 0, prevRight = 0, prevTop = 0, prevBottom = 0, desired_fps = 60, last_ticks = SDL_GetTicks(), index1 = 0, index2 = 0, enemyAnimate = 0, healthbarAnimate = 0, currentEnemy = 0, currentHealth = 0;
	Vector2f pos = knight.getPos(), pos0, speed0(1,1), speed;
	SDL_RendererFlip flipType = SDL_FLIP_NONE;
	bool collisionLeft = false, collisionRight = false, collisionTop = false, collisionBottom = false, firstLoop = true, 
		direction = true, death = false, isJumping = false, firstJump = false, jumping = false, gameRunning = true, falling = true, attack = false, moveDirection = false, enemyDirection = true, enemyFirstJump = false, enemyJumping = false, enemyIsJumping = false;
	//debug collision box
	bool collisionDebug = true;
	const float g = 9.81;
	std::map<int, bool> keyboard, up, down;

	t0=utils::hireTimeInSeconds();
	next_time = SDL_GetTicks() + TICK_INTERVAL;
	t1=utils::hireTimeInSeconds();
	int enemyRespawn = 0;

	enemy.setxPos(knight.getxPos() + 300);

	knight.setyPos(627-192);
	enemy.setyPos(460);

	while (gameRunning)
	{
		if ((int)(SDL_GetTicks() - last_ticks) < 1000/desired_fps) {
        	//continue;
	    } 

	    // std::cout << "Y: " << pos.y << "\r";
	    last_ticks = SDL_GetTicks();
		//std::cout << SDL_PollEvent(&event) << std::endl;
		// int startTicks = SDL_GetTicks();
		float newTime = utils::hireTimeInSeconds();
		float frameTime = newTime - currentTime;
		currentTime = newTime;
		pos = knight.getPos();
		// std::cout << pos.getx() << ", " << pos.gety() << std::endl;

		accumulator += frameTime;

		if(firstLoop) { prevLeft = (int)pos.getx() + 14 + 46; prevRight = (int)pos.getx() + (50/0.55) + 46; prevTop = (int)pos.gety() + 3 + 39; prevBottom = (int)pos.gety() + (50/0.55) + 39 + 90; firstLoop = false; current = idle1;}
		else { prevLeft = left; prevRight = right; prevTop = top; prevBottom = bottom; }
		if(prevRight == prevLeft) if(prevLeft == prevTop){prevBottom += 1;}

		left = (int)pos.getx() + 14 + 46;
		right = (int)pos.getx() + (50/0.55) + 46;
		top = (int)pos.gety() + 3 + 39;
		bottom = (int)pos.gety() + (50/0.55) + 39 + 90;

		window.clear();

		//change screen at -150 and 1250 x (left and right off screen), skies need to fill 1280x633
		//sky
		if(currentBack % 3 == 0){
			//735x414
			window.render(sky,1, 1.742, 1.53);
			for(Entity& e: grassEntities){
					window.render(e, 4, 4, 4);
			}
		}
		//render(Entity& p_entity, float factor_pos, float factor_w, float factor_h)
		//hell ground = 1350x860 sky = 850,850
		if(currentBack % 3 == 1 || currentBack % 3 == -1){
			window.render(hellSky, 1, 1.506, 0.745);
			for(Entity& i: hellEntities){
					window.render(i, 3.33, 0.24, 0.24);
			}
		}
		//beach ground = 500x500 sky = 600,400
		if(currentBack % 3 == 2 || currentBack % 3 == -2){
			window.render(beachSky,1, 2.1334, 1.583);
			for(Entity& o: beachEntities){
					window.render(o, 4, 0.256, 0.265);
			}
		}

		while (SDL_PollEvent(&event) && !jumping && !falling)
		{
			switch(event.type)
	        {
	            case SDL_KEYDOWN:
	                keyboard[event.key.keysym.sym] = false;
	                down[event.key.keysym.sym] = true;
	                up[event.key.keysym.sym] = false;
	                break;
	            case SDL_KEYUP:
	                keyboard[event.key.keysym.sym] = true;
	                up[event.key.keysym.sym] = true;
	                down[event.key.keysym.sym] = false;
	                break;
	        }
				if (event.type == SDL_QUIT){gameRunning = false;}
				if (event.key.keysym.scancode == SDL_SCANCODE_4) 	  {current = idle1;   move = -1; deathCounter = 0;death = false;}
				else if (event.key.keysym.scancode == SDL_SCANCODE_C) 	  {current = crouch;  move = -1; deathCounter = 0;death = false;}
				else if (event.key.keysym.scancode == SDL_SCANCODE_D) 	  {current = run;	  move = 1; deathCounter = 0;death = false; direction = true; collisionLeft = false; collisionTop = false; collisionBottom = false;}
				else if (event.key.keysym.scancode == SDL_SCANCODE_A) 	  {current = run;	  move = 0; deathCounter = 0;death = false; direction = false; collisionRight = false; collisionTop = false; collisionBottom = false;}
				//else if (event.key.keysym.scancode == SDL_SCANCODE_W) 	  {current = run;	  move = 2; deathCounter = 0;death = false;}
				else if (event.key.keysym.scancode == SDL_SCANCODE_S) 	  {current = run;	  move = 3; deathCounter = 0;death = false;}
				else if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {current = jump2;    deathCounter = 0; death = false; firstJump = true; jumping = true;}
				else if (event.key.keysym.scancode == SDL_SCANCODE_T) 	  {current = mid;     move = -1; deathCounter = 0;death = false;}
				else if (event.key.keysym.scancode == SDL_SCANCODE_F) 	  {current = fall;    move = -1; deathCounter = 0;death = false;}
				else if (event.key.keysym.scancode == SDL_SCANCODE_V) 	  {current = slide;   move = -1; deathCounter = 0;death = false;}
				else if (event.key.keysym.scancode == SDL_SCANCODE_G) 	  {current = grab;    move = -1; deathCounter = 0;death = false;}
				else if (event.key.keysym.scancode == SDL_SCANCODE_H) 	  {current = climb;   move = -1; deathCounter = 0;death = false;}
				else if (event.key.keysym.scancode == SDL_SCANCODE_P) 	  {current = idle2;   move = -1; deathCounter = 0;death = false;}
				else if (event.key.keysym.scancode == SDL_SCANCODE_1) 	  {current = attack1; move = -1; deathCounter = 0;death = false;attack = true;}
				else if (event.key.keysym.scancode == SDL_SCANCODE_2) 	  {current = attack2; move = -1; deathCounter = 0;death = false;attack = true;}
				else if (event.key.keysym.scancode == SDL_SCANCODE_3) 	  {current = attack3; move = -1; deathCounter = 0;death = false;attack = true;}
				else if (event.key.keysym.scancode == SDL_SCANCODE_9) 	  {collisionDebug = !collisionDebug;}
				else if (event.key.keysym.scancode == SDL_SCANCODE_Z) 	  {current = hurt;	  move = -1; deathCounter = 0;death = false;}
				else if (event.key.keysym.scancode == SDL_SCANCODE_X) 	  {current = die;	  move = -1; deathCounter = 0; death = true;}
				else if (event.key.keysym.scancode == SDL_SCANCODE_0) 	  {current = jump;	  deathCounter = 0;death = false; firstJump = true; jumping = true;}
				if (event.type == SDL_KEYUP) 				  {current = idle1; move = -1; index = 0; deathCounter = 0;}
		}
		while (SDL_PollEvent(&event) && jumping){
			if (event.key.keysym.scancode == SDL_SCANCODE_D) 	  {current = fall;	  move = 1; deathCounter = 0;death = false; direction =true;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_A) 	  {current = fall;	  move = 0; deathCounter = 0;death = false; direction = false;}
			if (event.type == SDL_KEYUP) 				  { move = -1; index = 0; deathCounter = 0;}
		}
		while (SDL_PollEvent(&event) && falling){
			if (event.key.keysym.scancode == SDL_SCANCODE_D) 	  {current = fall;	  move = 1; deathCounter = 0;death = false; direction = true; }
			else if (event.key.keysym.scancode == SDL_SCANCODE_A) 	  {current = fall;	  move = 0; deathCounter = 0;death = false; direction = false;}
			if (event.type == SDL_KEYUP) 				  { move = -1; index = 0; deathCounter = 0;}
		}
		// printf("%d 	\r", move);
		std::random_device dev;
    	std::mt19937 rng(dev());
    	std::uniform_int_distribution<std::mt19937::result_type> dist6(50,1220); // distribution in range [1, 6]
    	// std::cout << dist6(rng) << std::endl;
    	
		if((long long unsigned int)index == current.size()){index = 0;}
		
		//sprites are 50x37
		auto p = current[index];
		deathCounter++;
		if(deathCounter >= 6 && death == true){p = {9,5};}
		
		//first to 10 second to 5
		int mod = 6;
		if(current == attack1) mod = 7;
		if(current == attack2 || current == attack3) mod = 8;
		if(spriteAnimate % mod == 0 || spriteAnimate == 0){
			currentXAnimation = 0+(50*p.second);
			currentYAnimation = 0+(37*p.first);
			//renderSprite(Entity& p_entity, float factor_pos, float factor_w, float factor_h, Vector2f sprite_pos, Vector2f sprite_size)
			if(direction) {window.renderSprite(knight, 1, 0.55, 0.55, Vector2f(0+(50*p.second), 0+(37*p.first)), Vector2f(50,37));}
			if(!direction) {
				flipType = SDL_FLIP_HORIZONTAL;
				window.renderFlip(knight, 1, 0.55, 0.55, Vector2f((float)(0+(50*p.second)),(float)(0+(37*p.first))), Vector2f(50,37), degrees, NULL, flipType);
			}
		}
		//this causes stuttering on sprite
		else{
			index++;
			if(direction) {window.renderSprite(knight, 1, 0.55, 0.55, Vector2f(currentXAnimation,currentYAnimation), Vector2f(50,37));}
			if(!direction) {
				flipType = SDL_FLIP_HORIZONTAL;
				window.renderFlip(knight, 1, 0.55, 0.55, Vector2f(currentXAnimation,currentYAnimation), Vector2f(50,37), degrees,NULL, flipType);
			}
		}
		spriteAnimate++;
		
		//-1 no move, 0 left, 1 right, 2 up, 3 down
		// float moveSpeed = getMoveSpeed((float)window.getRefreshRate());
		// if(right >= 850) {knight.setxPos(prevRight - (50/0.55) - 46); std::cout << "collision right     "; collisionRight = true;}
		// if(left <= 150) {knight.setxPos(prevLeft - 14 - 46); std::cout << "collision left     "; collisionLeft = true;}
		//ground collision
		// if(bottom > 630) {knight.setyPos(prevBottom - (50/0.55) - 39 - 90); collisionBottom = true; }
		float moveSpeed = 5;
		if(move == 0 && collisionLeft == false){knight.moveLeft(moveSpeed);}
		if(move == 1 && collisionRight == false){knight.moveRight(moveSpeed);}
		if(move == 2 && collisionTop == false){knight.moveUp(moveSpeed);}
		if(move == 3 && collisionBottom == false){knight.moveDown(moveSpeed);}
		Vector2f currentPos =  knight.getPos();
		if(currentPos.getx() == pos.getx() && p.second == 1 && p.first == 1){current = idle1;}
		
		if(death == true){window.render(gameOverText, 0.5, 0.5, 0.5);}

		//character is 21x32, sprite is 37x50
		left = (int)pos.getx() + 14 + 46;
		right = (int)pos.getx() + (50/0.55) + 46;
		top = (int)pos.gety() + 3 + 39;
		bottom = (int)pos.gety() + (50/0.55) + 39 + 90;
		// printf("  Vertical: %d, %d  Horizontil: %d, %d   \r", left, right, top, bottom);

		if(jumping){knight.jump(firstJump, pos0, speed, speed0, t0, knight, t, collisionBottom, isJumping, move, direction, jumping, bottom, current, run, idle1, g, collisionBox);};

		//1100x1100
		collisionBox.setxPos((int)knight.getxPos());
		collisionBox.setyPos((int)knight.getyPos());
		if(collisionBox.getxPos() < 0){ knight.setxPos(0); }
		if(collisionBox.getxPos()+1100*0.08 > 1280){ knight.setxPos(1280 - (90));}

		if(collisionBox.getyPos()+192 > 630 && !falling){ 
			current = idle1; 
			knight.setyPos((int)(627-192)); falling = false;
		}
		if(!jumping) t = utils::hireTimeInSeconds() - t0;
		if(collisionBox.getyPos()+192 < 628 && !jumping && falling){ 
			current = fall; knight.moveDown(pos0.y - (speed0.y*t-g*6*t*t));
			if(collisionBox.getyPos()+192 >= 627) {falling = false;}
		}
		//std::cout << collisionBox.getxPos() << ", " << collisionBox.getyPos() << "  " << collisionBox.getxPos()+1100*0.08 << ", " << collisionBox.getyPos()+192 << "	";
		// std::cout << collisionBox.getxPos()*collisionBox.getyPos() << "   \r";
		// std::cout << collisionBox.getyPos()+192 << "	\r";
		if(collisionDebug) window.render(collisionBox, 1, 0.08, 0.175);
		
		auto l = enemyMove[index1];
		
		if(moveDirection == false){
			enemy.moveRight(1);
			if(enemy.getxPos() > 1100) {moveDirection = true; enemyDirection = !enemyDirection;}
		} 
		if(moveDirection == true) {
			enemy.moveLeft(1);
			if(enemy.getxPos() < 100) {moveDirection = false; enemyDirection = !enemyDirection;}
		}
		if(enemyAnimate == 0 || enemyAnimate % 8 == 0) {
			currentEnemy = 0 + (715/3)*l;
			flipType = SDL_FLIP_HORIZONTAL;
			if(!enemyDirection && index2 < 5) window.renderSprite(enemy, 1, 0.25, 0.6, Vector2f(currentEnemy, 0), Vector2f(715/3,349));
			if(enemyDirection && index2 < 5) window.renderFlip(enemy, 1, 0.25, 0.6, Vector2f(currentEnemy, 0), Vector2f(715/3,349), degrees,NULL, flipType);
		}
		else{
			flipType = SDL_FLIP_HORIZONTAL;
			if(!enemyDirection && index2 < 5) window.renderSprite(enemy, 1, 0.25, 0.6, Vector2f(currentEnemy, 0), Vector2f(715/3,349));
			if(enemyDirection && index2 < 5) window.renderFlip(enemy, 1, 0.25, 0.6, Vector2f(currentEnemy, 0), Vector2f(715/3,349), degrees,NULL, flipType);
		}
		index1++;
		if(index1 >= (int)enemyMove.size()) index1 = 0;

		healthbar.setyPos(enemy.getyPos() - 5);
		healthbar.setxPos(enemy.getxPos() + 30);

		bool left = collisionBox.getxPos()-130 < enemy.getxPos();
		bool right = collisionBox.getxPos()+192+40 > enemy.getxPos()+75;
		printf("%d, %d 		\r", left, right);

		//printf("%d, %d | %d, %d 		\r", (int)(collisionBox.getxPos()-10) ,(int)(collisionBox.getxPos()+192+10), (int)(enemy.getxPos())    , (int)(enemy.getxPos()+75));
		if((current == attack1 || current == attack2 || current == attack3) && attack && (collisionBox.getxPos()-130 < enemy.getxPos() && collisionBox.getxPos()+192+40 > enemy.getxPos()+75)) {
			index2++; 
			attack = false;
			enemyFirstJump = true;
		}
		enemy.jumpEnemy(enemyFirstJump, pos0, speed, speed0, t0, enemy, t, collisionBottom, enemyIsJumping, enemyDirection, direction, enemyJumping, bottom, g, knight);
		auto i = healthbarMove[index2];
		if(index2 < 6) window.renderSprite(healthbar, 1, 0.25, 0.05, Vector2f(0, 0+((431/5)*i)), Vector2f(457,431/5));
		//if(index2 >= (int)healthbarMove.size()) index2 = 0;
		// printf("%d		\r", enemyRespawn);
		if(index2 >= 5) enemyRespawn++;
		if(enemyRespawn > 100) {
			index2 = 0; enemyRespawn = 0;
			if(knight.getxPos() >= 640) enemy.setxPos(knight.getxPos() - 300);
			if(knight.getxPos() < 640) enemy.setxPos(knight.getxPos() + 300);
		}
		healthbarAnimate++;
		enemyAnimate++;

		window.display();

		SDL_Delay(time_left());
        next_time += TICK_INTERVAL;
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}