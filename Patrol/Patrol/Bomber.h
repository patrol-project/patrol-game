#pragma once

#include "GameObjectFactory.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "Enemy.h"

#include <iostream>
#include <math.h>

class Bomber : public Enemy {

public:
	Bomber();

	virtual ~Bomber();
	virtual void collision();
	virtual void update();

protected:
	int m_dyingTime;
	int m_health;
	int m_bulletFiringSpeed;
};

class BomberCreator : public BaseCreator {

public:
	virtual GameObject* createGameObject() const;
};

