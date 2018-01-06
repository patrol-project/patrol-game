#pragma once

#include"GameState.h"
#include "GameObject.h"
#include <vector>

/**
 * @brief In this state the menu is showed on the screen with corresponding game object on it.
 * 
 */
class MenuState : public GameState
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
	virtual string getStateID() const { return menuId; }
private:
	static const string menuId; ///< state name
	vector<GameObject*> gameObjects; ///< vector with all game objects for this state
	static void menuToPlay(); ///< loads the menu to the screen
	static void exitFromMenu(); ///< exits from the menu and quits the game
};
