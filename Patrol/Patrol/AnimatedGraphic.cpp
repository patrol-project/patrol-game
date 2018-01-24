#include "AnimatedGraphic.h"

void AnimatedGraphic::load(std::unique_ptr<LoaderParams> const &pParams)
{
	ShooterObject::load(pParams);
	animationSpeed = pParams->getAnimSpeed();
}

void AnimatedGraphic::draw()
{
	ShooterObject::draw();
}

void AnimatedGraphic::update()
{
	m_currentFrame = int(((SDL_GetTicks() / (1000 / animationSpeed)) % 2));

	ShooterObject::update();
}

void AnimatedGraphic::clean()
{
}
