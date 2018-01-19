#pragma once

#include "MenuState.h"
#include "GameObject.h"
#include <vector>

/**
 * @brief This is the state when the game is paused with the ESCAPE key
 * 
 */
class PauseState : public MenuState
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
	virtual string getStateID() const { return pauseID; }
private:
	virtual void setCallbacks(const std::vector<Callback>& callbacks);
	static void pauseToMain(); ///< pauses the game and shows the menu
	static void resumePlay(); ///< exits from menu and resumes the game
	static const string pauseID; ///< returns the name of the state
	vector<GameObject*> gameObjects; ///< stores all game objects which are in this state
};