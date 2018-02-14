#include "ScoreboardState.h"
#include "StateParser.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "MenuButton.h"
#include "Game.h"

const std::string ScoreboardState::scoreboardID = "SCOREBOARD";

void ScoreboardState::update()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->update();
	}
}

void ScoreboardState::render()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->draw();
	}
	TextureManager::Instance()->drawScoreboard(&m_records);
}

bool ScoreboardState::onEnter()
{
	StateParser stateParser;
	stateParser.parseState("States.xml", scoreboardID, &gameObjects, &m_textureIDList);

	ScoreboardParser scoresParser;
	scoresParser.parseScores("Resources/scores.xml", &m_records);

	m_callbacks.push_back(0);
	m_callbacks.push_back(s_returnToMain);
	// set the callbacks for menu items
	setCallbacks(m_callbacks);
	m_loadingComplete = true;
	std::cout << "entering ScoreboardState\n";
	return true;
}

bool ScoreboardState::onExit()
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

	std::cout << "exiting ScoreboardState\n";
	return true;
}

void ScoreboardState::setCallbacks(const std::vector<Callback>& callbacks)
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

void ScoreboardState::s_returnToMain()
{
	Game::Instance().getStateMachine()->set_next_state(STATE_MAIN_MENU);
}
