#include "Turret.h"
#include "Game.h"
#include "BulletHandler.h"
#include "Camera.h"

Turret::Turret() :
	m_dyingTime(1000), m_health(10), m_bulletFiringSpeed(80) {}

Turret::~Turret() {}

void Turret::collision() {
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

void Turret::update() {
	if (!m_bDying) {
		m_position.setX(xPos - Camera::Instance()->getPosition().getX());
		if (m_bulletCounter == m_bulletFiringSpeed) {
			BulletHandler::Instance()->addEnemyBullet(m_position.getX(), m_position.getY() + 42, 16, 16, "bullet2", 1, Vector2D(-3, 3));
			BulletHandler::Instance()->addEnemyBullet(m_position.getX() + 20, m_position.getY() + 42, 16, 16, "bullet2", 1, Vector2D(0, 3));
			BulletHandler::Instance()->addEnemyBullet(m_position.getX() + 40, m_position.getY() + 42, 16, 16, "bullet2", 1, Vector2D(3, 3));
			m_bulletCounter = 0;
		}

		m_bulletCounter++;
	}
	else {
		doDyingAnimation();
	}
}

GameObject* TurretCreator::createGameObject() const {
	return new Turret();
}
