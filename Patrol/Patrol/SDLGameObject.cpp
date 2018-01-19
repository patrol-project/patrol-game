#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Game.h"

SDLGameObject::SDLGameObject() : GameObject()
{
}

void SDLGameObject::load(const LoaderParams *pParams)
{
	position = Vector2D(pParams->getX(), pParams->getY());
	velocity = Vector2D(0, 0);
	acceleration = Vector2D(0, 0);
	width = pParams->getWidth();
	height = pParams->getHeight();
	textureID = pParams->getTextureID();
	currentRow = 1;
	currentFrame = 1;
	numberOfFrames = pParams->getNumberOfFrames();
}

void SDLGameObject::draw()
{
	if (velocity.getX() > 0)
	{
		TextureManager::Instance()->drawFrame(
			textureID,
			(int)position.getX(),
			(int)position.getY(),
			width,
			height,
			currentRow,
			currentFrame,
			Game::Instance().getRenderer(),
			SDL_FLIP_HORIZONTAL);
	}
	else
	{
		TextureManager::Instance()->drawFrame(
			textureID,
			(int)position.getX(),
			(int)position.getY(),
			width,
			height,
			currentRow,
			currentFrame,
			Game::Instance().getRenderer()
		);
	}
}

void SDLGameObject::update()
{
	position += velocity;
	velocity += acceleration;
}

void SDLGameObject::clean()
{
}