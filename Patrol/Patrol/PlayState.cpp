#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"
#include "Player.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "Enemy.h"

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