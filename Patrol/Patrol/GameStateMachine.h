#pragma once

#include "GameState.h"
#include <vector>

// Game states
enum GameStates
{
	STATE_NULL,
	STATE_MAIN_MENU,
	STATE_PLAY,
	STATE_PAUSE_MENU,
	STATE_GAME_OVER,
	STATE_EXIT
};

/**
 * @brief Responsible for controlling and managing all game states.
 *
 */
class GameStateMachine
{
public:
	GameStateMachine();
	/**
	 * @brief Changes from current to the given state
	 * First call onExit() on the current state, then onEnter() on the
	 * given state and continues it's work with the new given state
	 *
	 * @param state the state to which we will change
	 */
	void changeState();

	//State status manager
	void set_next_state(int newState);

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
	//State variables
	int stateID;
	int nextState;

	//Game state object
	GameState *currentState;
};
