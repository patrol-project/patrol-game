#include "TextureManager.h"
#include <SDL_image.h>

TextureManager* TextureManager::texture_instance = 0;

bool TextureManager::load(string fileName, string id, SDL_Renderer * renderer)
{
	SDL_Surface* tempSurface = IMG_Load(fileName.c_str());

	if (tempSurface == 0) {
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	// everything went ok, add the texture to our list

	if (texture != 0)
	{
		textureMap[id] = texture;
		return true;
	}

	// reaching here mean sth went wrong
	return false;
}

void TextureManager::draw(string id, int x, int y, int width, int height, SDL_Renderer * renderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(renderer, textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer * renderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopyEx(renderer, textureMap[id], &srcRect,
		&destRect, 0, 0, flip);
}

void TextureManager::clearAllTexturesFromMap()
{
	for (auto i = textureMap.begin(); i != textureMap.end(); i++) {
		if (i->second != nullptr) {
			SDL_DestroyTexture(i->second);
			i->second = nullptr;
		}
	}
	textureMap.clear();
}