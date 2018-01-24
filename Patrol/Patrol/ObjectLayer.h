#pragma once
#include "Layer.h"
#include <vector>
#include "GameObject.h"
#include "CollisionManager.h"
#include "Vector2D.h"
#include "Game.h"
#include "Level.h"

#include <iostream>

class GameObject;

class ObjectLayer : public Layer {

public:
	virtual ~ObjectLayer();

	// pass a level object through
	virtual void update(Level* pLevel);
	virtual void render();

	std::vector<GameObject*>* getGameObjects();

private:
	// check for collisions between game objects
	CollisionManager m_collisionManager;

	// a list of game objects
	std::vector<GameObject*> m_gameObjects;
};