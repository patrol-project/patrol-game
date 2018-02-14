#include "TextureManager.h"
#include <SDL_image.h>
#include <iostream>
#include "Game.h"

TextureManager* TextureManager::texture_instance = 0;

bool TextureManager::load(string fileName, string id, SDL_Renderer * renderer)
{
	SDL_Surface* tempSurface = IMG_Load(fileName.c_str());

	if (tempSurface == 0) {
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	// start of font setting 

	int fontsize = 24;
	string fontpath = "Resources/Fonts/Roboto-Regular.ttf";	
	TTF_Init();
	font = TTF_OpenFont(fontpath.c_str(), fontsize);
	// end of font setting
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

void TextureManager::drawFrame(string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer * renderer, double angle, int alpha, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = width * currentFrame;
	srcRect.y = height * currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_SetTextureAlphaMod(textureMap[id], alpha);
	SDL_RenderCopyEx(renderer, textureMap[id], &srcRect, &destRect, angle, 0, flip);
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

void TextureManager::clearFromTextureMap(string id)
{
	SDL_DestroyTexture(textureMap[id]);
	textureMap.erase(id);
}

void TextureManager::drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = margin + (spacing + width) * currentFrame;
	srcRect.y = margin + (spacing + height) * currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, textureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

void TextureManager::drawScoreboard(vector<ScoreRecord> *results)
{
	string text = "";

	for (int i = 0; i < results->size(); i++) {
		ScoreRecord curr;
		curr.name = results->at(i).name;
		curr.points = results->at(i).points;
		text += curr.name + " - " + curr.points + "\n";
	}

	SDL_Texture* ftexture = NULL; // our font-texture

	SDL_Color text_color = { 0,0,0 };
	int t_width = 0; // width of the loaded font-texture
	int t_height = 0; // height of the loaded font-texture

	// check to see that the font was loaded correctly
	if (font == NULL) {
		cout << "Failed the load the font!\n";
		cout << "SDL_TTF Error: " << TTF_GetError() << "\n";
	}
	else {
		// now create a surface from the font
		SDL_Surface* text_surface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), text_color, 400);

		// render the text surface
		if (text_surface == NULL) {
			cout << "Failed to render text surface!\n";
			cout << "SDL_TTF Error: " << TTF_GetError() << "\n";
		}
		else {
			// create a texture from the surface
			ftexture = SDL_CreateTextureFromSurface(Game::Instance().getRenderer(), text_surface);

			if (ftexture == NULL) {
				cout << "Unable to create texture from rendered text!\n";
			}
			else {
				t_width = text_surface->w; // assign the width of the texture
				t_height = text_surface->h; // assign the height of the texture
				int x = 0;
				int y = 0;
				SDL_Rect dst = { x, y, t_width, t_height };
				SDL_RenderCopy(Game::Instance().getRenderer(), ftexture, NULL, &dst);
				
				// clean up after ourselves (destroy the surface)
				SDL_FreeSurface(text_surface);
			}
		}
	}	
	SDL_DestroyTexture(ftexture);
}

void TextureManager::updateScoreboard()
{
}

