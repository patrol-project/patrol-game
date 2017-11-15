//SDL header file
#include <SDL.h>
#include <SDL_image.h>
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

//Loads individual image as texture
SDL_Texture* loadTexture(char* path);

//The window we'll be rendering to
SDL_Window* window = NULL;

//The window renderer
SDL_Renderer* renderer = NULL;

//Current displayed texture
SDL_Texture* texture = NULL;

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
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

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
			//Create renderer for window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_JPG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;
	
	//Default image path
	char* defaultTexturePath = "Resources/mainBackground.jpg";

	//Load PNG texture
	texture = loadTexture(defaultTexturePath);
	if (texture == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded image
	SDL_DestroyTexture(texture);
	texture = NULL;

	//Destroy window	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}	

//void stretchSurface()
//{
//	SDL_Rect stretchRect;
//	stretchRect.x = 0;
//	stretchRect.y = 0;
//	stretchRect.w = SCREEN_WIDTH;
//	stretchRect.h = SCREEN_HEIGHT;
//	SDL_BlitScaled(currentSurface, NULL, screenSurface, &stretchRect);
//
//	//Update the surface
//	SDL_UpdateWindowSurface(window);
//}

SDL_Texture* loadTexture(char* path)
{
	//The final optimized//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path);
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
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

				//Clear screen
				SDL_RenderClear(renderer);

				//Render texture to screen
				SDL_RenderCopy(renderer, texture, NULL, NULL);

				//Update screen
				SDL_RenderPresent(renderer);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}