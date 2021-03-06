//SDL header file
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "Game.h"

const int SCREEN_WIDTH = 640; ///< window width
const int SCREEN_HEIGHT = 480; ///< window height
const char* GAME_NAME = "Patrol"; ///< window title

/**
 * @brief SDL-required arguments for multi-platform
 * 
 * @param argc 
 * @param args 
 * @return int 
 */
int main(int argc, char* args[])
{
	/**
	 * @brief Initialize the Game Instance
	 * 
	 */
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
	//The frames per second timer
	LTimer fpsTimer;

	//The frames per second cap timer
	LTimer capTimer;
	int countedFrames = 0;

	/**
	 * @brief Load media needed for the start of the game
	 * 
	 */
	if (!Game::Instance().loadMedia())
	{
		printf("Failed to load media!\n");
		return 2;
	}

	const int SCREEN_FPS = 90;
	const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;


	/**
	 * @brief Main game loop
	 * 
	 */
	while (Game::Instance().get_running())
	{
		fpsTimer.start();
		capTimer.start();
		Game::Instance().handleInput();

		Game::Instance().update();

		Game::Instance().getStateMachine()->changeState();

		Game::Instance().render();
		//Calculate and correct fps
		float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
		if (avgFPS > 2000000)
		{
			avgFPS = 0;
		}
		++countedFrames;
		int frameTicks = capTimer.getTicks();
		if (frameTicks < SCREEN_TICKS_PER_FRAME)
		{
			//Wait remaining time
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
		}
	}

	/**
	 * @brief Free resources and clean SDL
	 * 
	 */
	Game::Instance().clean();

	return 0;
}