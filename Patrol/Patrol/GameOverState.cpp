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
