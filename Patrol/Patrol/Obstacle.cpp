#include "Obstacle.h"
#include "Game.h"
#include "BulletHandler.h"
#include "Camera.h"

Obstacle::Obstacle() :
	m_dyingTime(1000), m_health(10) {}

Obstacle::~Obstacle() {}

void Obstacle::collision() {
	m_health -= 1;

	if (m_health == 0) {
		if (!m_bPlayedDeathSound) {
			SoundManager::Instance()->playSound("explode", 0);

			m_textureID = "largeexplosion";
			m_currentFrame = 0;
			m_numFrames = 13;
			m_width = 60;
			m_height = 60;
			m_bDying = true;
		}
	}
}

void Obstacle::update() {
	if (!m_bDying) {
		m_position.setX(xPos - Camera::Instance()->getPosition().getX());
	}
	else {
		doDyingAnimation();
	}
}

GameObject* ObstacleCreator::createGameObject() const {
	return new Obstacle();
}
