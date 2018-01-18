#include "PauseState.h"
#include "MenuState.h"
#include "MenuButton.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "Game.h"

const std::string PauseState::pauseID = "PAUSE";

void PauseState::pauseToMain()
{
	Game::Instance().getStateMachine()->set_next_state(STATE_MAIN_MENU);
}

void PauseState::resumePlay()
{
	Game::Instance().getStateMachine()->set_next_state(STATE_PLAY);
}

void PauseState::update()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->update();
	}
}

void PauseState::render()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->draw();
	}
}

bool PauseState::onEnter()
{
	if (!TextureManager::Instance()->load("Resources/resume.png", "resumebutton", Game::Instance().getRenderer()))
	{
		return false;
	}

	if (!TextureManager::Instance()->load("Resources/main.png", "mainbutton", Game::Instance().getRenderer()))
	{
		return false;
	}

	GameObject* button1 = new MenuButton(new LoaderParams(200, 100, 200, 80, "mainbutton"), pauseToMain);
	GameObject* button2 = new MenuButton(new LoaderParams(200, 300, 200, 80, "resumebutton"), resumePlay);
	
	gameObjects.push_back(button1);
	gameObjects.push_back(button2);
	
	return true;
}

bool PauseState::onExit()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->clean();
	}

	gameObjects.clear();
	
	TextureManager::Instance()->clearFromTextureMap("resumebutton");
	TextureManager::Instance()->clearFromTextureMap("mainbutton");
	// reset the mouse button states to false
	InputHandler::Instance()->reset();

	return true;
}