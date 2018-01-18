#include "MenuState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "PlayState.h"

const string MenuState::menuId = "MENU";

void MenuState::update()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->update();
	}
}

void MenuState::render()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->draw();
	}
}

bool MenuState::onEnter()
{
	if (!TextureManager::Instance()->load("Resources/play.png", "playbutton", Game::Instance().getRenderer()))
	{
		return false;
	}
	
	if (!TextureManager::Instance()->load("Resources/exit.png", "exitbutton", Game::Instance().getRenderer()))
	{
		return false;
	}

	GameObject* playBtn = new MenuButton(new LoaderParams(100, 100, 400, 100, "playbutton"), menuToPlay);
	GameObject* exitBtn = new MenuButton(new LoaderParams(100, 300, 400, 100, "exitbutton"), exitFromMenu);

	gameObjects.push_back(playBtn);
	gameObjects.push_back(exitBtn);
	
	return true;
}

bool MenuState::onExit()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->clean();
	}

	gameObjects.clear();
	TextureManager::Instance()->clearFromTextureMap("playbutton");
	TextureManager::Instance()->clearFromTextureMap("exitbutton");
	
	return true;
}

void MenuState::menuToPlay()
{
	Game::Instance().getStateMachine()->set_next_state(STATE_PLAY);
}
void MenuState::exitFromMenu()
{
	Game::Instance().quit();
}