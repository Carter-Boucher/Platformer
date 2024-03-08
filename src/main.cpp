#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <random>

// #include <random>
// #include <iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Math.hpp"
#include "utils.hpp"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

	RenderWindow window("GAME v1.0", SCREEN_WIDTH, SCREEN_HEIGHT);

	//grass ground
	SDL_Texture* grassTexture = window.loadTexture("res/gfx/ground_grass_1.png");
	std::vector<Entity> grassEntities = {Entity(Vector2f(0, 156), grassTexture, Vector2f(32,32)),
					Entity(Vector2f(30, 156), grassTexture, Vector2f(32,32)),
					Entity(Vector2f(60, 156), grassTexture, Vector2f(32,32)),
					Entity(Vector2f(90, 156), grassTexture, Vector2f(32,32)),
					Entity(Vector2f(120, 156), grassTexture, Vector2f(32,32)),
					Entity(Vector2f(150, 156), grassTexture, Vector2f(32,32)),
					Entity(Vector2f(180, 156), grassTexture, Vector2f(32,32)),
					Entity(Vector2f(210, 156), grassTexture, Vector2f(32,32)),
					Entity(Vector2f(240, 156), grassTexture, Vector2f(32,32)),
					Entity(Vector2f(270, 156), grassTexture, Vector2f(32,32)),
					Entity(Vector2f(300, 156), grassTexture, Vector2f(32,32))};
	//blue sky			
	SDL_Texture* skyTexture = window.loadTexture("res/gfx/sky.png");
	Entity sky(Vector2f(0, 0), skyTexture, Vector2f(735,414));

	//beach
	SDL_Texture* beachSkyTexture = window.loadTexture("res/gfx/sunset.png");
	Entity beachSky(Vector2f(0, 0), beachSkyTexture, Vector2f(600,400));
	//500x500
	SDL_Texture* beachGroundTexture = window.loadTexture("res/gfx/sand.png");
	std::vector<Entity> beachEntities = {Entity(Vector2f(0, 156), beachGroundTexture, Vector2f(500,500)),
					Entity(Vector2f(30, 156), beachGroundTexture, Vector2f(500,500)),
					Entity(Vector2f(60, 156), beachGroundTexture, Vector2f(500,500)),
					Entity(Vector2f(90, 156), beachGroundTexture, Vector2f(500,500)),
					Entity(Vector2f(120, 156), beachGroundTexture, Vector2f(500,500)),
					Entity(Vector2f(150, 156), beachGroundTexture, Vector2f(500,500)),
					Entity(Vector2f(180, 156), beachGroundTexture, Vector2f(500,500)),
					Entity(Vector2f(210, 156), beachGroundTexture, Vector2f(500,500)),
					Entity(Vector2f(240, 156), beachGroundTexture, Vector2f(500,500)),
					Entity(Vector2f(270, 156), beachGroundTexture, Vector2f(500,500)),
					Entity(Vector2f(300, 156), beachGroundTexture, Vector2f(500,500))};

	//hell
	SDL_Texture* hellSkyTexture = window.loadTexture("res/gfx/hell.png");
	Entity hellSky(Vector2f(0, 0), hellSkyTexture, Vector2f(850,850));
	//1350x860
	SDL_Texture* hellGroundTexture = window.loadTexture("res/gfx/rock.png");
	std::vector<Entity> hellEntities = {Entity(Vector2f(0, 156), hellGroundTexture, Vector2f(1450,860)),
					Entity(Vector2f(50, 156), hellGroundTexture, Vector2f(1450,860)),
					Entity(Vector2f(100, 156), hellGroundTexture, Vector2f(1450,860)),
					Entity(Vector2f(150, 156), hellGroundTexture, Vector2f(1450,860)),
					Entity(Vector2f(200, 156), hellGroundTexture, Vector2f(1450,860)),
					Entity(Vector2f(250, 156), hellGroundTexture, Vector2f(1450,860)),
					Entity(Vector2f(300, 156), hellGroundTexture, Vector2f(1450,860)),
					Entity(Vector2f(350, 156), hellGroundTexture, Vector2f(1450,860)),
					Entity(Vector2f(400, 156), hellGroundTexture, Vector2f(1450,860))};

	//sprites are 50x37, 350x407
	SDL_Texture* kinghtTexture = window.loadTexture("res/gfx/adventurer-sheet.png");
	Entity knight(Vector2f(400, 408), kinghtTexture, Vector2f(350,407));
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

	SDL_Texture* cannonBallTexture = window.loadTexture("res/gfx/cannonBall.png");
	Entity cannonBall(Vector2f(0, 510), cannonBallTexture, Vector2f(170,170));

	SDL_Texture* gameOverTextTex = window.loadTexture("res/gfx/game_over.png");
	Entity gameOverText(Vector2f(700, 100), gameOverTextTex, Vector2f(1080,1080));

	bool gameRunning = true;
	SDL_Event event;

	//const float timeStep = 0.01f;
	float accumulator = 0.0f;
	float currentTime = utils::hireTimeInSeconds();
	int index = 0;
	int move = -1;
	Vector2f pos =  knight.getPos();
	int currentBack = 0;
	int deathCounter = 0;
	bool death = false;
	int ballCount = 0;
	int digit = 0;
	int spriteAnimate = -1;
	float currentXAnimation = 0.f, currentYAnimation = 0.f;

	while (gameRunning)
	{
		//std::cout << SDL_PollEvent(&event) << std::endl;
		int startTicks = SDL_GetTicks();
		float newTime = utils::hireTimeInSeconds();
		float frameTime = newTime - currentTime;
		currentTime = newTime;
		pos = knight.getPos();
		accumulator += frameTime;

		window.clear();

		//change screen at -150 and 1250 x (left and right off screen), skies need to fill 1280x633
		//sky

		if(currentBack == 0){
			//735x414
			window.render(sky,1, 1.742, 1.53);
			//ground
			for(Entity& e: grassEntities){
					window.render(e, 4, 4, 4);
			}
		}
		//render(Entity& p_entity, float factor_pos, float factor_w, float factor_h)
		//hell ground = 1350x860 sky = 850,850
		if(currentBack < 0){
			window.render(hellSky, 1, 1.506, 0.745);
			//ground
			for(Entity& i: hellEntities){
					window.render(i, 3.33, 0.24, 0.24);
			}
		}
		//beach ground = 500x500 sky = 600,400
		if(currentBack > 0){
			window.render(beachSky,1, 2.1334, 1.583);
			//ground
			for(Entity& o: beachEntities){
					window.render(o, 4, 0.256, 0.265);
			}
		}

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT){gameRunning = false;}
			if (event.key.keysym.scancode == SDL_SCANCODE_4) 	  {current = idle1;   move = -1; deathCounter = 0;death = false;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_C) 	  {current = crouch;  move = -1; deathCounter = 0;death = false;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_D) 	  {current = run;	  move = 1; deathCounter = 0;death = false;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_A) 	  {current = run;	  move = 0; deathCounter = 0;death = false;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_W) 	  {current = run;	  move = 2; deathCounter = 0;death = false;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_S) 	  {current = run;	  move = 3; deathCounter = 0;death = false;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {current = jump;    move = -1; deathCounter = 0;death = false;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_T) 	  {current = mid;     move = -1; deathCounter = 0;death = false;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_F) 	  {current = fall;    move = -1; deathCounter = 0;death = false;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_V) 	  {current = slide;   move = -1; deathCounter = 0;death = false;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_G) 	  {current = grab;    move = -1; deathCounter = 0;death = false;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_H) 	  {current = climb;   move = -1; deathCounter = 0;death = false;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_P) 	  {current = idle2;   move = -1; deathCounter = 0;death = false;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_1) 	  {current = attack1; move = -1; deathCounter = 0;death = false;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_2) 	  {current = attack2; move = -1; deathCounter = 0;death = false;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_3) 	  {current = attack3; move = -1; deathCounter = 0;death = false;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_Z) 	  {current = hurt;	  move = -1; deathCounter = 0;death = false;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_X) 	  {current = die;	  move = -1; deathCounter = 0; death = true;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_0) 	  {current = jump2;	  move = -1; deathCounter = 0;death = false;}
			if (event.type == SDL_KEYUP) 				  {current == idle1;  move = -1; index = 0; deathCounter = 0;}
		}

		std::random_device dev;
    	std::mt19937 rng(dev());
    	std::uniform_int_distribution<std::mt19937::result_type> dist6(50,1220); // distribution in range [1, 6]
    	// std::cout << dist6(rng) << std::endl;
    	ballCount++;
    	
    	if(ballCount % 150 == 0 || digit == 0){
    		digit = dist6(rng);
    		if(digit < knight.getxPos()+50 && digit >= knight.getxPos()){
    			digit +=50;
    		}
    		if(digit > knight.getxPos()-50 && digit <= knight.getxPos()){
    			digit +=50;
    		}
    		cannonBall.setxPos(digit);
    	}
    	//std::cout << digit << std::endl;
    	if(digit >= 640){cannonBall.moveLeft(3);}
    	if(digit < 640){cannonBall.moveRight(3);}
    	
    	if((cannonBall.getxPos() <= knight.getxPos() && knight.getxPos() <= cannonBall.getxPos()+25) 
    		|| (cannonBall.getxPos()-25 <= knight.getxPos() && knight.getxPos() <= cannonBall.getxPos())){
    		death = true;
    		if(deathCounter < 6){
    			deathCounter = 0;
    		}
    	}
    	
		if((long long unsigned int)index == current.size()){index = 0;}
		
		//sprites are 50x37
		auto p = current[index];
		//std::cout << p.first << ", " << p.second << std::endl;
		deathCounter++;
		if(deathCounter >= 6 && death == true){p = {9,5};}
		//std::cout << "death: " << deathCounter << " sprite: " << p.first << ", " << p.second << " bool: " << death << std::endl;
		
		//first to 10 second to 5
		spriteAnimate++;
		if(spriteAnimate % 5 == 0 || spriteAnimate == 0){
			currentXAnimation = 0+(50*p.second);
			currentYAnimation = 0+(37*p.first);
			window.renderSprite(knight, 1, 0.55, 0.55, Vector2f((float)(0+(50*p.second)),(float)(0+(37*p.first))), Vector2f(50,37));
		}
		else{
			window.renderSprite(knight, 1, 0.55, 0.55, Vector2f(currentXAnimation,currentYAnimation), Vector2f(50,37));
		}

		if((current == attack1 || current == attack2 || current == attack3) && ((cannonBall.getxPos() <= knight.getxPos() && knight.getxPos() <= cannonBall.getxPos()+50) || (cannonBall.getxPos()-50 <= knight.getxPos() && knight.getxPos() <= cannonBall.getxPos()))){
			std::cout << "here" <<std::endl;
		}
		else{
			window.render(cannonBall, 1, 0.4, 0.4);
		}
		
		//-1 no move, 0 left, 1 right, 2 up, 3 down
		if(move == 0){knight.moveLeft(5);}
		if(move == 1){knight.moveRight(5);}
		if(move == 2){knight.moveUp(5);}
		if(move == 3){knight.moveDown(5);}
		index++;
		Vector2f currentPos =  knight.getPos();
		if(currentPos.getx() == pos.getx() && p.second == 1 && p.first == 1){current = idle1;}
		//std::cout << "pos: " << knight.getxPos() <<std::endl;
		if(knight.getxPos() < -150){
			//std::cout << knight.getxPos() <<std::endl;
			currentBack--;
			knight.setxPos(1250);
		}
		if(knight.getxPos() > 1250){
			currentBack++;
			knight.setxPos(-150);
		}
		//std::cout << "currentPos: " << currentPos.getx() << ", pos: " << pos.getx() << std::endl;
		
		if(death == true){
			window.render(gameOverText, 0.5, 0.5, 0.5);
		}

		window.display();
		//SDL_RenderPresent(window.getRenderer());

		//std::cout << "GetTicks: " << SDL_GetTicks() << " startTicks: " << startTicks << std::endl;
		int frameTicks = (int)SDL_GetTicks() - startTicks;
		//std::cout << "FrameTicks: " << frameTicks << std::endl;
		//std::cout << "refreshRate: " << window.getRefreshRate() << " divide: " << 1000/window.getRefreshRate() << std::endl;
		//std::cout<< window.getRefreshRate()<<std::endl;
		if(frameTicks < 1000/window.getRefreshRate()){
			//std::cout << 1000/window.getRefreshRate() << std::endl;
			SDL_Delay(1000/window.getRefreshRate());
		}
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}