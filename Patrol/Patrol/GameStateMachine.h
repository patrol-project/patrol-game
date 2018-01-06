#pragma once

#include "GameState.h"
#include <vector>

/**
 * @brief Responsible for controlling and managing all game states.
 * 
 */
class GameStateMachine
{
public:
	/**
	 * @brief Adds the given state to the vector and runs it
	 * 
	 * @param state some game state
	 */
	void pushState(GameState* state);

	/**
	 * @brief Changes from current to the given state
	 * First call onExit() on the current state, then onEnter() on the 
	 * given state and continues it's work with the new given state
	 *
	 * @param state the state to which we will change
	 */
	void changeState(GameState* state);

	/**
	 * @brief Checks if there are states in the vector.
	 * If yes calls onExit() and removes it from the vector
	 * If no returns doing nothing
	 * 
	 */
	void popState();

	/**
	 * @brief Calls the update method on the current state
	 * 
	 */
	void update();

	/**
	 * @brief Calls the render method on the current state
	 * 
	 */
	void render();
private:
	vector<GameState*> gameStates; ///< Keep all game states in the vector so that we can push and pop them
};
