#include "Bomber.h"
#include "Game.h"
#include "BulletHandler.h"
#include "Camera.h"

Bomber::Bomber() :
	m_dyingTime(1000), m_health(10), m_bulletFiringSpeed(80), m_movementSpeed(20), m_distanceToTravel(400), m_distanceTravelled(0) {}

Bomber::~Bomber() {}

void Bomber::collision() {
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

void Bomber::update() {
	if (!m_bDying) {
		m_position.setX(xPos - Camera::Instance()->getPosition().getX());
		if (m_bulletCounter == m_bulletFiringSpeed) {
			
			BulletHandler::Instance()->addEnemyBullet(m_position.getX() + 30, m_position.getY() + 42, 32, 32, "missle", 1, Vector2D(0, 3));
			
			xPos -= m_movementSpeed;
			m_distanceTravelled += m_movementSpeed;
			
			if (m_distanceTravelled == m_distanceToTravel)
			{
				m_movementSpeed *= -1;
				m_distanceToTravel *= -1;
				m_distanceTravelled = 0;
			}
			
			m_bulletCounter = 0;
		}

		m_bulletCounter++;
	}
	else {
		doDyingAnimation();
	}
}

GameObject* BomberCreator::createGameObject() const {
	return new Bomber();
}
