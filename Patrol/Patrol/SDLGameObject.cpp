#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Game.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams) : GameObject(pParams)
, position(pParams->getX(), pParams->getY())
, velocity(0, 0)
, acceleration(0, 0)
{
	width = pParams->getWidth();
	height = pParams->getHeight();
	textureID = pParams->getTextureID();
	currentRow = 1;
	currentFrame = 1;
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