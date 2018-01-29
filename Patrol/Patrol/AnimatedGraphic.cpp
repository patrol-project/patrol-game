#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic()
	: animationSpeed(0), numberOfFrames(0)
{ }
AnimatedGraphic::~AnimatedGraphic()
{
}
void AnimatedGraphic::load(std::unique_ptr<LoaderParams> const &pParams)
{
	ShooterObject::load(std::move(pParams));
	animationSpeed = pParams->getAnimSpeed();
}

void AnimatedGraphic::draw()
{
	ShooterObject::draw();
}

void AnimatedGraphic::update()
{
	// in the end it should be 2 instead of numberOfFrames var because crashes..
	m_currentFrame = int(((SDL_GetTicks() / (1000 / animationSpeed)) % 2));
}

void AnimatedGraphic::clean()
{
	ShooterObject::clean();
}

GameObject* AnimatedGraphicCreator::createGameObject() const {
	return new AnimatedGraphic();
}
