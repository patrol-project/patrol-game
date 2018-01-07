#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic(const LoaderParams* pParams, int animSpeed) : SDLGameObject(pParams), animationSpeed(animSpeed)
{
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
