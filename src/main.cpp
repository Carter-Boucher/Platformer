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

	//sprites are 64*64
    SDL_Texture* kinghtTextureIdle = window.loadTexture("res/gfx/hulking_knight.png");
    Entity knightIdle(Vector2f(100, 525), kinghtTextureIdle, Vector2f(320, 128));

    SDL_Texture* kinghtTextureRun = window.loadTexture("res/gfx/hulking_knight.png");
    Entity knightRun(Vector2f(400, 525), kinghtTextureRun, Vector2f(320, 128));

	bool gameRunning = true;

	SDL_Event event;

	const float timeStep = 0.01f;
	float accumulator = 0.0f;
	float currentTime = utils::hireTimeInSeconds();
	int knightFrame = 0;

	while (gameRunning)
	{
		int startTicks = SDL_GetTicks();
		float newTime = utils::hireTimeInSeconds();
		float frameTime = newTime - currentTime;
		currentTime = newTime;

		accumulator += frameTime;
		// Get our controls and events
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
					gameRunning = false;
		}

		// while(accumulator >= timeStep){
		// 	// Get our controls and events
		// 	while (SDL_PollEvent(&event))
		// 	{
		// 		if (event.type == SDL_QUIT)
		// 			gameRunning = false;
		// 	}
		// 	accumulator -= timeStep;
		// }

		//const float alpha = accumulator / timeStep;

		window.clear();

		window.render(sky,1, 1.742, 1.53);

		for(Entity& e: entities){
			window.render(e, 4, 4, 4);
		}
		window.display();

		knightFrame++;
		if(knightFrame >= 6){
			knightFrame = 0;
		}

		//renderSprite(Entity& p_entity, float factor_pos, float factor_w, float factor_h, Vector2f sprite_pos, Vector2f sprite_size)
		//sprite size 64x64
		//idle 
		for(int i = 0; i < 5; i++){
			window.renderSprite(knightIdle, 1, 1, 1, Vector2f(0+(64*i),64), Vector2f(64,64));
			window.display();
		}

		//run 
		for(int j = 0; j < 5; j++){
			window.renderSprite(knightRun, 1, 1, 1, Vector2f(0+(64*j),0), Vector2f(64,64));
			window.display();
		}

		

		int frameTicks = SDL_GetTicks() - startTicks;
		std::cout<< window.getRefreshRate()<<std::endl;

		SDL_RenderPresent(window.getRenderer());
		//SDL_Delay(16.66666);

		if(frameTicks < 1000/window.getRefreshRate()){
			SDL_Delay(1000/window.getRefreshRate());
		}
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}