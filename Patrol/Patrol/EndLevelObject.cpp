#include "EndLevelObject.h"
#include "EndLevelObject.h"
#include "Game.h"
#include "BulletHandler.h"
#include "Camera.h"

EndLevelObject::EndLevelObject() :
	m_dyingTime(100000), m_health(10000)  {}

EndLevelObject::~EndLevelObject() {}

void EndLevelObject::collision() {
	Game::Instance().getStateMachine()->set_next_state(STATE_WIN);
}

void EndLevelObject::update() {
	if (!m_bDying) {
		m_position.setX(xPos - Camera::Instance()->getPosition().getX()); 
		m_currentFrame = int(((SDL_GetTicks() / (500)) % m_numFrames));
	}
}

GameObject* EndLevelObjectCreator::createGameObject() const {
	return new EndLevelObject();
}
