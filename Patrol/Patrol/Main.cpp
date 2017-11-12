//SDL header file
#include <SDL.h>
#include <stdio.h>

//Window dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//SDL-required arguments for multi-platform
int main(int argc, char* args[])
{
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;

	//Initializing SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		//Initialization debugging
		printf("SDL could not initialize! SDL error: %s\n", SDL_GetError());
	}
	else
	{
		//Initialize window
		window = SDL_CreateWindow(
			"Patrol", 
			SDL_WINDOWPOS_UNDEFINED, 
			SDL_WINDOWPOS_UNDEFINED, 
			SCREEN_WIDTH, 
			SCREEN_HEIGHT, 
			SDL_WINDOW_SHOWN);

		if (window == NULL)
		{
			printf("Window could not be initialized! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get window surface
			screenSurface = SDL_GetWindowSurface(window);

			//Fill the surface with red
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 255, 0, 0));

			//Update surface
			SDL_UpdateWindowSurface(window);

			//Delay closing for 2 seconds
			SDL_Delay(2000);
		}
	}

	//Destroy window and surface
	SDL_DestroyWindow(window);

	//Quit SDL
	SDL_Quit();

	return 0;
}