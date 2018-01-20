#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"
#include "Player.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "Enemy.h"
#include "GameOverState.h"
#include "StateParser.h"
#include "LevelParser.h"

const string PlayState::playId = "PLAY";

void PlayState::update()
{
	pLevel->render();

	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance().getStateMachine()->set_next_state(STATE_PAUSE_MENU);
	}
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->update();
	}
}

void PlayState::render()
{
	pLevel->render();

	/*for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->draw();
	}*/
}

bool PlayState::onEnter()
{
	LevelParser levelParser;
	pLevel = levelParser.parseLevel("Resources/levels/level1.tmx");

	// parse the state
 	StateParser stateParser;
	stateParser.parseState("States.xml", playId, &gameObjects, &m_textureIDList);
	std::cout << "entering PlayState\n";

	return true;
}

bool PlayState::onExit()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->clean();
	}
	gameObjects.clear();

	for (int i = 0; i < m_textureIDList.size(); i++)
	{
		TextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}
	return true;
}