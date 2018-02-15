#pragma once

#include "GameObjectFactory.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "Enemy.h"

#include <iostream>
#include <math.h>

class EndLevelObject : public Enemy {

public:
	EndLevelObject();

	virtual ~EndLevelObject();
	virtual void collision();
	virtual void update();

	virtual std::string type() { return "EndLevelObject"; }
protected:
	int m_dyingTime;
	int m_health;
};

class EndLevelObjectCreator : public BaseCreator {

public:
	virtual GameObject* createGameObject() const;
};

