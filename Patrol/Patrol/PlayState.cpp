#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"
#include "Player.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "Enemy.h"
#include "GameOverState.h"

const string PlayState::playId = "PLAY";

void PlayState::update()
{
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance().getStateMachine()->pushState(new PauseState());
	}
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->update();
	}
	if (checkCollision(dynamic_cast<SDLGameObject*>(gameObjects[0]), dynamic_cast<SDLGameObject*>(gameObjects[1])))
	{
		Game::Instance().getStateMachine()->pushState(new GameOverState());
	}
}

void PlayState::render()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->draw();
	}
}

bool PlayState::onEnter()
{
	if (!TextureManager::Instance()->load("Resources/alien.png", "alien", Game::Instance().getRenderer()))
	{
		return false;
	}

	if (!TextureManager::Instance()->load("Resources/knight.png", "knight", Game::Instance().getRenderer()))
	{
		return false;
	}

	GameObject* player = new Player(new LoaderParams(100, 100, 91, 100, "alien"));
	GameObject* enemy = new Enemy(new LoaderParams(400, 100, 100, 120, "knight"));
	
	gameObjects.push_back(player);
	gameObjects.push_back(enemy);
	return true;
}

bool PlayState::onExit()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->clean();
	}
	gameObjects.clear();
	TextureManager::Instance()->clearFromTextureMap("alien");
	return true;
}

bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;
	leftA = p1->getPosition().getX();
	rightA = p1->getPosition().getX() + p1->getWidth();
	topA = p1->getPosition().getY();
	bottomA = p1->getPosition().getY() + p1->getHeight();
	//Calculate the sides of rect B
	leftB = p2->getPosition().getX();
	rightB = p2->getPosition().getX() + p2->getWidth();
	topB = p2->getPosition().getY();
	bottomB = p2->getPosition().getY() + p2->getHeight();
	//If any of the sides from A are outside of B
	if (bottomA <= topB) { return false; }
	if (topA >= bottomB) { return false; }
	if (rightA <= leftB) { return false; }
	if (leftA >= rightB) { return false; }
	return true;
}