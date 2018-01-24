#include "PauseState.h"
#include "MenuState.h"
#include "MenuButton.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "Game.h"
#include "StateParser.h"

const std::string PauseState::pauseID = "PAUSE";

void PauseState::pauseToMain()
{
	Game::Instance().getStateMachine()->set_next_state(STATE_RESET_GAME);
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
	StateParser stateParser;
	stateParser.parseState("States.xml", pauseID, &gameObjects, &m_textureIDList);

	m_callbacks.push_back(0);
	m_callbacks.push_back(resumePlay);
	m_callbacks.push_back(pauseToMain);

	// set the callbacks for menu items
	setCallbacks(m_callbacks);

	m_loadingComplete = true;
	std::cout << "entering PauseState\n";
	return true;
}

bool PauseState::onExit()
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

	std::cout << "exiting PauseState\n";
	return true;
}

void PauseState::setCallbacks(const std::vector<Callback>& callbacks)
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
