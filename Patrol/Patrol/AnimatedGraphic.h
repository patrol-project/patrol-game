#pragma once

#include "SDLGameObject.h"

class AnimatedGraphic : public SDLGameObject
{
public:
	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void load(const LoaderParams* pParams);
private:
	int animationSpeed;
	int numberOfFrames;
};