//SDL header file
#include <SDL.h>
#include <stdio.h>

//Window dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Surfaces constants
enum SurfacesEnum
{
	SURFACE_DEFAULT,
	SURFACE_TOTAL
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface(char* path);

//Main window
SDL_Window* window = NULL;

//Surface contained by the window
SDL_Surface* screenSurface = NULL;

//Images corresponding to each surface
SDL_Surface* surfaces[SURFACE_TOTAL];

//Current displayed image
SDL_Surface* currentSurface = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		window = SDL_CreateWindow(
			"Patrol",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		//Initialization debugging
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			screenSurface = SDL_GetWindowSurface(window);
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;
	
	//Default image path
	char* defaultSurfacePath = "Resources/mainBackground.bmp";

	//Load default surface
	surfaces[SURFACE_DEFAULT] = loadSurface(defaultSurfacePath);
	if (surfaces[SURFACE_DEFAULT] == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", defaultSurfacePath, SDL_GetError());
		success = false;
	}

	return success;
}

void close()
{
	//Deallocate surfaces
	for (int i = 0; i < SURFACE_TOTAL; ++i)
	{
		SDL_FreeSurface(surfaces[i]);
		surfaces[i] = NULL;
	}

	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}	

SDL_Surface* loadSurface(char* path)
{
	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path);
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
	}

	return loadedSurface;
}

//SDL-required arguments for multi-platform
int main(int argc, char* args[])
{
	//Initializing SDL
	if (!init())
	{
		printf("SDL failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool shouldQuit = false;

			//Event handler
			SDL_Event event;

			//Set default current surface
			currentSurface = surfaces[SURFACE_DEFAULT];

			//Main loop
			while (!shouldQuit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&event) != 0)
				{
					//User requests quit
					if (event.type == SDL_QUIT)
					{
						shouldQuit = true;
					}
					//User presses a key
					else if (event.type == SDL_KEYDOWN)
					{
						//Handling key presses
						switch (event.key.keysym.sym)
						{
						case SDLK_UP:
							printf("Key pressed: [%s]\n", SDL_GetKeyName(event.key.keysym.sym));
							break;

						case SDLK_DOWN:
							printf("Key pressed: [%s]\n", SDL_GetKeyName(event.key.keysym.sym));
							break;

						case SDLK_LEFT:
							printf("Key pressed: [%s]\n", SDL_GetKeyName(event.key.keysym.sym));
							break;

						case SDLK_RIGHT:
							printf("Key pressed: [%s]\n", SDL_GetKeyName(event.key.keysym.sym));
							break;

						default:
							printf("Key pressed: [%s]\n", SDL_GetKeyName(event.key.keysym.sym));
							break;
						}
					}
				}

				//Apply the image
				SDL_BlitSurface(currentSurface, NULL, screenSurface, NULL);

				//Update the surface
				SDL_UpdateWindowSurface(window);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}