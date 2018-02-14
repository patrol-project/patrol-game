#pragma once

#include "MenuState.h"
#include "GameObject.h"
#include <vector>
#include "ScoreboardParser.h"

/**
* @brief This is the state when the game is paused with the ESCAPE key
*
*/
class ScoreboardState : public MenuState
{
public:
	/**
	* @brief Updates the game objects which are in this state.
	*
	*/
	virtual void update();

	/**
	* @brief Draws all game object which are in this state
	*
	*/
	virtual void render();

	/**
	* @brief Loads all needed resources when entering this state
	*
	* @return true if everything is loaded
	* @return false if something failed to load
	*/
	virtual bool onEnter();

	/**
	* @brief Cleans all resources which were loaded for this state
	*
	* @return true if everything is cleaned
	* @return false if something failed to free resources
	*/
	virtual bool onExit();

	/**
	* @brief returns current states name
	*
	* @return string getStateID
	*/
	virtual string getStateID() const { return scoreboardID; }
private:
	virtual void setCallbacks(const std::vector<Callback>& callbacks);
	static void s_returnToMain(); ///< pauses the game and shows the menu
	static const string scoreboardID; ///< returns the name of the state
	vector<GameObject*> gameObjects; ///< stores all game objects which are in this state
	vector<ScoreRecord> m_records;
};