#pragma once

#include <string>
#include "SDL.h"
#include <map>
#include <vector>
#include "ScoreboardParser.h"
#include <SDL_ttf.h>

using namespace std;

class TextureManager
{
public:
	bool load(string fileName, string id, SDL_Renderer* pRenderer);
	// draw
	void draw(string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	//draw frame
	void drawFrame(string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, double angle, int alpha, SDL_RendererFlip flip = SDL_FLIP_NONE);
	// clears all textures from the textureMap
	void clearAllTexturesFromMap();
	// clears texture by given id
	void clearFromTextureMap(string id);

	void drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer);

	std::map<std::string, SDL_Texture*> getTextureMap() { return textureMap; }

	void drawScoreboard(vector<SingleRecord*> *results);

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
	TTF_Font* font;
	void updateScoreboard();
};
