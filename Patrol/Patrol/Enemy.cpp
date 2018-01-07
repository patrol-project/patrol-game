#include "Enemy.h"

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams)
{
}

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
