#ifndef _Game_
#define _Game_

#include "SDL.h"

class Game
{
public:
	bool init(const char* title, int xpos, int ypos, int width, int height, bool showWindow);
	void handleInput();
	bool loadMedia();
	void update();
	void clean();
	bool get_running() const;

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

	SDL_Texture* loadTexture(char * path);

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
};
#endif // !_Game_
