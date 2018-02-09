#include "CollisionManager.h"
#include <memory>

const int CollisionManager::s_buffer = 4;

bool CollisionManager::RectRect(SDL_Rect* A, SDL_Rect* B)
{
	int aHBuf = A->h / s_buffer;
	int aWBuf = A->w / s_buffer;

	int bHBuf = B->h / s_buffer;
	int bWBuf = B->w / s_buffer;

	// if the bottom of A is less than the top of B - no collision
	if ((A->y + A->h) - aHBuf <= B->y + bHBuf) { return false; }

	// if the top of A is more than the bottom of B = no collision
	if (A->y + aHBuf >= (B->y + B->h) - bHBuf) { return false; }

	// if the right of A is less than the left of B - no collision
	if ((A->x + A->w) - aWBuf <= B->x + bWBuf) { return false; }

	// if the left of A is more than the right of B - no collision
	if (A->x + aWBuf >= (B->x + B->w) - bWBuf) { return false; }

	// otherwise there has been a collision
	return true;
}

void CollisionManager::checkPlayerEnemyBulletCollision(Player* pPlayer) {
	SDL_Rect* pRect1 = new SDL_Rect();
	pRect1->x = pPlayer->getPosition().getX();
	pRect1->y = pPlayer->getPosition().getY();
	pRect1->w = pPlayer->getWidth();
	pRect1->h = pPlayer->getHeight();

	for (unsigned int i = 0; i <
		BulletHandler::Instance()->getEnemyBullets().size(); i++) {
		auto pEnemyBullet = BulletHandler::Instance()->getEnemyBullets()[i];

		SDL_Rect* pRect2 = new SDL_Rect();
		pRect2->x = pEnemyBullet->getPosition().getX();
		pRect2->y = pEnemyBullet->getPosition().getY();

		pRect2->w = pEnemyBullet->getWidth();
		pRect2->h = pEnemyBullet->getHeight();

		if (RectRect(pRect1, pRect2)) {
			if (!pPlayer->dying() && !pEnemyBullet->dying()) {
				pEnemyBullet->collision();
				pPlayer->collision();
			}
		}
		delete pRect2;
	}
	delete pRect1;
}

void CollisionManager::checkEnemyPlayerBulletCollision(const std::vector<GameObject *> &objects)
{
	for (unsigned int i = 0; i < objects.size(); i++) {
		auto pObject = objects[i];

		for (unsigned int j = 0; j <
			BulletHandler::Instance()->getPlayerBullets().size(); j++) {
			if (pObject->type() != std::string("Enemy") || !pObject->updating()) {
				continue;
			}

			SDL_Rect* pRect1 = new SDL_Rect();
			pRect1->x = pObject->getPosition().getX();
			pRect1->y = pObject->getPosition().getY();
			pRect1->w = pObject->getWidth();
			pRect1->h = pObject->getHeight();

			auto pPlayerBullet = BulletHandler::Instance()->
				getPlayerBullets()[j];

			SDL_Rect* pRect2 = new SDL_Rect();
			pRect2->x = pPlayerBullet->getPosition().getX();
			pRect2->y = pPlayerBullet->getPosition().getY();
			pRect2->w = pPlayerBullet->getWidth();
			pRect2->h = pPlayerBullet->getHeight();

			if (RectRect(pRect1, pRect2)) {
				if (!pObject->dying() && !pPlayerBullet->dying()) {
					pPlayerBullet->collision();
					pObject->collision();
				}
			}
			delete pRect1;
			delete pRect2;
		}
	}
}

void CollisionManager::checkPlayerEnemyCollision(Player* pPlayer, const std::vector<GameObject*> &objects) {
	SDL_Rect* pRect1 = new SDL_Rect();
	pRect1->x = pPlayer->getPosition().getX();
	pRect1->y = pPlayer->getPosition().getY();
	pRect1->w = pPlayer->getWidth();
	pRect1->h = pPlayer->getHeight();

	for (unsigned int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->type() != std::string("Enemy") || !objects[i]->updating())
		{
			continue;
		}

		SDL_Rect* pRect2 = new SDL_Rect();
		pRect2->x = objects[i]->getPosition().getX();
		pRect2->y = objects[i]->getPosition().getY();
		pRect2->w = objects[i]->getWidth();
		pRect2->h = objects[i]->getHeight();

		if (RectRect(pRect1, pRect2))
		{
			if (!objects[i]->dead() && !objects[i]->dying()) {
				pPlayer->collision();
			}
		}
		delete pRect2;
	}
	delete pRect1;
}