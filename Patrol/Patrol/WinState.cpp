#include "WinState.h"

#include "Game.h"
#include "MenuState.h"
#include "PlayState.h"
#include "TextureManager.h"
#include "AnimatedGraphic.h"
#include "MenuButton.h"
#include "InputHandler.h"

const std::string WinState::winID = "WIN";

void WinState::setCallbacks(const std::vector<Callback>& callbacks)
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

void WinState::gameOverToMain()
{
	Game::Instance().getStateMachine()->set_next_state(STATE_MAIN_MENU);
}
void WinState::nextLevel()
{
	int currentLevel = Game::Instance().getCurrentLevel();
	Game::Instance().setCurrentLevel(currentLevel + 1);
}

void WinState::update()
{
	if (m_loadingComplete && !gameObjects.empty())
	{
		for (unsigned int i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i]->update();
		}
	}
}

void WinState::render()
{
	if (m_loadingComplete && !gameObjects.empty())
	{
		for (unsigned int i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i]->draw();
		}
	}
}

bool WinState::onEnter()
{
	// parse the state
	StateParser stateParser;
	stateParser.parseState("States.xml", winID, &gameObjects, &m_textureIDList);
	m_callbacks.push_back(0);
	m_callbacks.push_back(gameOverToMain);
	m_callbacks.push_back(nextLevel);
	// set the callbacks for menu items

	m_loadingComplete = true;

	setCallbacks(m_callbacks);
	std::cout << "entering WinState\n";
	return true;
}

bool WinState::onExit()
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

	std::cout << "exiting WinState\n";
	return true;
}
