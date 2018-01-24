#pragma once

#include "GameObjectFactory.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "Enemy.h"

#include <iostream>
#include <math.h>

class Turret : public Enemy {

public:
	Turret();

	virtual ~Turret();
	virtual void collision();
	virtual void update();

protected:
	int m_dyingTime;
	int m_health;
	int m_bulletFiringSpeed;
};

class TurretCreator : public BaseCreator {

public:
	virtual GameObject* createGameObject() const;
};

