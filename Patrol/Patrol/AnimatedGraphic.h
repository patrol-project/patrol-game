#pragma once

#include "ShooterObject.h"

class AnimatedGraphic : public ShooterObject
{
public:
	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void load(std::unique_ptr<LoaderParams> const &pParams);
private:
	int animationSpeed;
	int numberOfFrames;
};