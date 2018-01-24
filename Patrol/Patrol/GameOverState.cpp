#include "GameOverState.h"
#include "Game.h"
#include "MenuState.h"
#include "PlayState.h"
#include "TextureManager.h"
#include "AnimatedGraphic.h"
#include "MenuButton.h"
#include "InputHandler.h"

const std::string GameOverState::gameOverID = "GAMEOVER";

void GameOverState::setCallbacks(const std::vector<Callback>& callbacks)
{
	// go through the game objects
	if (!gameObjects.empty())
	{
		for (unsigned int i = 0; i < gameObjects.size(); i++)
		{
			// if they are of type MenuButton then assign a callback based on the id passed in from the file
			if (dynamic_cast<MenuButton*>(gameObjects[i]))
			{
				MenuButton* pButton = dynamic_cast<MenuButton*>(gameObjects[i]);
				pButton->setCallback(callbacks[pButton->getCallbackID()]);
			}
		}
	}
}

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
	// parse the state
	StateParser stateParser;
	stateParser.parseState("States.xml", gameOverID, &gameObjects, &m_textureIDList);
	m_callbacks.push_back(0);
	m_callbacks.push_back(gameOverToMain);
	m_callbacks.push_back(restartPlay);
	// set the callbacks for menu items
	setCallbacks(m_callbacks);
	std::cout << "entering GameOverState\n";
	return true;
}

bool GameOverState::onExit()
{
	m_exiting = true;

	// clean the game objects
	if (m_loadingComplete && !gameObjects.empty())
	{
		gameObjects.back()->clean();
		gameObjects.pop_back();
	}

	gameObjects.clear();


	// clear the texture manager
	for (unsigned int i = 0; i < m_textureIDList.size(); i++)
	{
		TextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}

	// reset the input handler
	InputHandler::Instance()->reset();

	std::cout << "exiting GameOverState\n";
	return true;
}
