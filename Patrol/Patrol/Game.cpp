#include "Game.h"
#include <stdio.h>
#include <SDL_image.h>
#include "InputHandler.h"
#include "TextureManager.h"

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool showWindow)
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Warning: Linear texture filtering not enabled!");
	}

	//Create window
	int showWindowFlag = showWindow == true ? SDL_WINDOW_SHOWN : 0;
	window = SDL_CreateWindow(title, xpos, ypos, width, height, showWindowFlag);

	//Initialization debugging
	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	//Create renderer for window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	//Initialize renderer color
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	//Initialize PNG loading
	int imgFlags = IMG_INIT_JPG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}

	// start game loop
	running = true;

	return true;
}

void Game::clean()
{
	//Free loaded images
	TextureManager::Instance()->clearAllTexturesFromMap();

	//Destroy window	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void Game::quit()
{
	running = false;
}

void Game::handleInput()
{
	InputHandler::Instance()->update();
}

bool Game::loadMedia()
{
	//Default image path
	char* defaultTexturePath = "Resources/mainBackground.jpg";

	//Load PNG texture
	bool success = TextureManager::Instance()->load(defaultTexturePath, "background", Game::Instance().getRenderer());

	return success;
}

void Game::update()
{
	//Clear screen
	SDL_RenderClear(renderer);

	// draw background
	TextureManager::Instance()->draw("background", 0, 0, 640, 480, Game::Instance().getRenderer());

	//Update screen
	SDL_RenderPresent(renderer);
}

bool Game::get_running() const
{
	return running;
}