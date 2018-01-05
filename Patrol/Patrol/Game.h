#pragma once

#include "SDL.h"
#include "GameStateMachine.h"

class Game
{
public:
	bool init(const char* title, int xpos, int ypos, int width, int height, bool showWindow);
	void handleInput();
	bool loadMedia();
	void update();
	void clean();
	void quit();
	void render();
	bool get_running() const;
	SDL_Renderer* getRenderer() const { return renderer; }
	GameStateMachine* getStateMachine() const { return gameStateMachine; }

	// Make Game class singleton to ensure there is no second 
	// instance of the same class
	static Game& Instance()
	{
		static Game instance;

		return instance;
	}

	Game(Game const&) = delete;
	void operator=(Game const&) = delete;
private:
	Game() { }

	bool running;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;

	GameStateMachine* gameStateMachine;
};
