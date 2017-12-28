//SDL header file
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "Game.h"

//Window dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const char* GAME_NAME = "Patrol";

//SDL-required arguments for multi-platform
int main(int argc, char* args[])
{
	//Initializing SDL
	if (!Game::Instance().init(GAME_NAME,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		true)
		)
	{
		printf("SDL failed to initialize!\n");
		return 1;
	}

	//Load media
	if (!Game::Instance().loadMedia())
	{
		printf("Failed to load media!\n");
		return 2;
	}

		//Main loop
	while (Game::Instance().get_running())
	{
		Game::Instance().handleInput();

		Game::Instance().update();
	}

	//Free resources and close SDL
	Game::Instance().clean();

	return 0;
}