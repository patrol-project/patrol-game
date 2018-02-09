#include "ObjectLayer.h"
#include "Camera.h"


ObjectLayer::~ObjectLayer() {
	for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)// < m_gameObjects.size(); i++)
	{
		delete (*it);
	}
	m_gameObjects.clear();
}

// return a pointer to this layers objects, the level parser will fill this
std::vector<GameObject*>* ObjectLayer::getGameObjects() 
{
	return &m_gameObjects; 
}

void ObjectLayer::update(Level* pLevel) {
	// checks bullets
	m_collisionManager.checkPlayerEnemyBulletCollision(pLevel->getPlayer());
	m_collisionManager.checkEnemyPlayerBulletCollision((const std::vector<GameObject*>&)m_gameObjects);

	// check game objects
	m_collisionManager.checkPlayerEnemyCollision(pLevel->getPlayer(), (const std::vector<GameObject*>&)m_gameObjects);

	// iterate through the objects
	if (!m_gameObjects.empty())
	{
		for (auto it = m_gameObjects.begin(); it != m_gameObjects.end();)// < m_gameObjects.size(); i++)
		{
			if ((*it)->getPosition().getX() <= Camera::Instance()->getPosition().getX() + Game::Instance().getGameWidth()) {
				(*it)->setUpdating(true);
				(*it)->update();
			}
			else
			{
				if ((*it)->type() != std::string("Player"))
				{
					(*it)->setUpdating(false);
				}
				else
				{
					(*it)->update();
				}
			}

			// check if dead or off screen
			if ((*it)->dead() || (*it)->getPosition().getY() > Game::Instance().getGameHeight()) 
			{
				delete * it;
				it = m_gameObjects.erase(it); // erase from vector and get new iterator
			}
			else
			{
				++it; // increment if all ok
			}

		}
	}
}

void ObjectLayer::render()
{
	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}