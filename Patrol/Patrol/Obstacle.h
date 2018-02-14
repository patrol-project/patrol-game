#pragma once

#include "GameObjectFactory.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "Enemy.h"

#include <iostream>
#include <math.h>

class Obstacle : public Enemy {

public:
	Obstacle();

	virtual ~Obstacle();
	virtual void collision();
	virtual void update();

protected:
	int m_dyingTime;
	int m_health;
};

class ObstacleCreator : public BaseCreator {

public:
	virtual GameObject* createGameObject() const;
};

