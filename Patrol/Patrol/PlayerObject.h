#pragma once

#include "TextureManager.h"
#include "GameObject.h"

class PlayerObject : public GameObject
{
public:

	virtual ~PlayerObject() {}

	virtual void load(std::unique_ptr<LoaderParams> const &pParams);

	virtual void draw();
	virtual void update();

	virtual void clean() {}
	virtual void collision() {}

	virtual std::string type() { return "SDLGameObject"; }

protected:

	PlayerObject();

	void doDyingAnimation();

	int m_bulletFiringSpeed;
	int m_bulletCounter;
	int m_moveSpeed;

	// how long the death animation takes, along with a counter
	int m_dyingTime;
	int m_dyingCounter;

	// has the explosion sound played?
	bool m_bPlayedDeathSound;
};
