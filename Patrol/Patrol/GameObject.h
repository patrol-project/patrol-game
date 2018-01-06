#pragma once

#include "LoaderParams.h"

/**
 * @brief Abstract base class with pure virtual functions to 
 * set a blueprint for all the game objects we are creating.
 * 
 */
class GameObject
{
public:
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;
protected:
	GameObject(const LoaderParams* pParams) {}
	virtual ~GameObject() {}
};