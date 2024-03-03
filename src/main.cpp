#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Math.hpp"
#include "utils.hpp"

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

	RenderWindow window("GAME v1.0", 1280, 720);

	SDL_Texture* grassTexture = window.loadTexture("res/gfx/ground_grass_1.png");

	std::vector<Entity> entities = {Entity(Vector2f(0, 156), grassTexture, Vector2f(32,32)),
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

	SDL_Texture* skyTexture = window.loadTexture("res/gfx/sky.png");
	Entity sky(Vector2f(0, 0), skyTexture, Vector2f(735,414));

	//SDL_Texture* knigtTexture = window.loadTexture("res/gfx/hulking_knight.png");
	//Entity knight(Vector2f(120, 100), knigtTexture);

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

	bool gameRunning = true;
	SDL_Event event;

	//const float timeStep = 0.01f;
	float accumulator = 0.0f;
	float currentTime = utils::hireTimeInSeconds();
	int index = 0;
	int move = -1;
	Vector2f pos =  knight.getPos();

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

		//sky
		window.render(sky,1, 1.742, 1.53);
		//ground
		for(Entity& e: entities){
				window.render(e, 4, 4, 4);
		}

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT){gameRunning = false;}
			if (event.key.keysym.scancode == SDL_SCANCODE_4) 	  {current = idle1;   move = -1;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_C) 	  {current = crouch;  move = -1;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_D) 	  {current = run;	  move = 1;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_A) 	  {current = run;	  move = 0;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {current = jump;    move = -1;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_T) 	  {current = mid;     move = -1;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_F) 	  {current = fall;    move = -1;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_V) 	  {current = slide;   move = -1;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_G) 	  {current = grab;    move = -1;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_H) 	  {current = climb;   move = -1;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_P) 	  {current = idle2;   move = -1;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_1) 	  {current = attack1; move = -1;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_2) 	  {current = attack2; move = -1;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_3) 	  {current = attack3; move = -1;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_Z) 	  {current = hurt;	  move = -1;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_X) 	  {current = die;	  move = -1;}
			else if (event.key.keysym.scancode == SDL_SCANCODE_0) 	  {current = jump2;	  move = -1;}
			if (event.type == SDL_KEYUP) 				  {current == idle1;  move = -1; index = 0;}
		}
		
		if((long long unsigned int)index == current.size()){
			index = 0;
		}
		
		//sprites are 50x37
		auto p = current[index];
		//std::cout << p.first << ", " << p.second << std::endl;
		SDL_Delay(75);
		
		//first to 10 second to 5
		window.renderSprite(knight, 1, 0.55, 0.55, Vector2f((float)(0+(50*p.second)),(float)(0+(37*p.first))), Vector2f(50,37));
		if(move == 0){
			knight.moveLeft();
		}
		if(move == 1){
			knight.moveRight();
		}
		index++;
		Vector2f currentPos =  knight.getPos();
		if(currentPos.getx() == pos.getx() && p.second == 1 && p.first == 1){
			current = idle1;
		}
		//std::cout << "currentPos: " << currentPos.getx() << ", pos: " << pos.getx() << std::endl;
		
		int frameTicks = SDL_GetTicks() - startTicks;
		//std::cout<< window.getRefreshRate()<<std::endl;
		window.display();
		//SDL_RenderPresent(window.getRenderer());

		if(frameTicks < 1000/window.getRefreshRate()){
			//SDL_Delay(1000/window.getRefreshRate());
		}
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}