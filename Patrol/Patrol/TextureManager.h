#pragma once

#include <string>
#include "SDL.h"
#include <map>

using namespace std;

class TextureManager
{
public:
	bool load(string fileName, string id, SDL_Renderer* pRenderer);
	// draw
	void draw(string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	//draw frame
	void drawFrame(string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	// clears all textures from the textureMap
	void clearAllTexturesFromMap();

	static TextureManager* Instance()
	{
		if (texture_instance == 0)
		{
			texture_instance = new TextureManager();
			return texture_instance;
		}
		return texture_instance;
	}
private:
	map<string, SDL_Texture*> textureMap;
	TextureManager() {}
	static TextureManager* texture_instance;
};
