#pragma once

#include "ShooterObject.h"
#include "GameObjectFactory.h"

class AnimatedGraphic : public ShooterObject
{
public:
	AnimatedGraphic();
	virtual ~AnimatedGraphic();

	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void load(std::unique_ptr<LoaderParams> const &pParams);
private:
	int animationSpeed;
	int numberOfFrames;
};

class AnimatedGraphicCreator : public BaseCreator {

public:
	virtual GameObject* createGameObject() const;
};
