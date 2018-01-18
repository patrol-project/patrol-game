#include "GameOverState.h"
#include "Game.h"
#include "MenuState.h"
#include "PlayState.h"
#include "TextureManager.h"
#include "AnimatedGraphic.h"
#include "MenuButton.h"
#include "InputHandler.h"

const std::string GameOverState::gameOverID = "GAMEOVER";

void GameOverState::gameOverToMain()
{
	Game::Instance().getStateMachine()->set_next_state(STATE_MAIN_MENU);
}
void GameOverState::restartPlay()
{
	Game::Instance().getStateMachine()->set_next_state(STATE_PLAY);
}

void GameOverState::update()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->update();
	}
}

void GameOverState::render()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->draw();
	}
}

bool GameOverState::onEnter()
{
	if (!TextureManager::Instance()->load("Resources/gameover.png", "gameovertext", Game::Instance().getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("Resources/main.png", "mainbutton", Game::Instance().getRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->load("Resources/restart.png", "restartbutton", Game::Instance().getRenderer()))
	{
		return false;
	}
	GameObject* gameOverText = new AnimatedGraphic(new LoaderParams(200, 100, 190, 30, "gameovertext"), 2);
	GameObject* button1 = new MenuButton(new LoaderParams(200, 200, 200, 80, "mainbutton"), gameOverToMain);
	GameObject* button2 = new MenuButton(new LoaderParams(200, 300, 200, 80, "restartbutton"), restartPlay);
	
	gameObjects.push_back(gameOverText);
	gameObjects.push_back(button1);
	gameObjects.push_back(button2);

	return true;
}

bool GameOverState::onExit()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->clean();
	}

	gameObjects.clear();

	TextureManager::Instance()->clearFromTextureMap("gameovertext");
	TextureManager::Instance()->clearFromTextureMap("mainbutton");
	TextureManager::Instance()->clearFromTextureMap("restartbutton");
	// reset the mouse button states to false
	InputHandler::Instance()->reset();

	return true;
}
