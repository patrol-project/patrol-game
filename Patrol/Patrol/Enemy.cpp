#include "Enemy.h"

void Enemy::draw()
{
	SDLGameObject::draw();
}

void Enemy::update()
{
	currentFrame = int(((SDL_GetTicks() / 100) % 1));

	SDLGameObject::update();
}

void Enemy::clean()
{
}
void Enemy::load(const LoaderParams * pParams)
{
	SDLGameObject::load(pParams);
}
