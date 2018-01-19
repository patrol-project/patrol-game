#include "AnimatedGraphic.h"

void AnimatedGraphic::load(const LoaderParams * pParams)
{
	SDLGameObject::load(pParams);
	animationSpeed = pParams->getAnimSpeed();
}

void AnimatedGraphic::draw()
{
	SDLGameObject::draw();
}

void AnimatedGraphic::update()
{
	currentFrame = int(((SDL_GetTicks() / (1000 / animationSpeed)) % 2));

	SDLGameObject::update();
}

void AnimatedGraphic::clean()
{
}
