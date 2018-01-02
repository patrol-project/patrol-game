#include "GameStateMachine.h"
#include <iostream>

void GameStateMachine::pushState(GameState *state)
{
	gameStates.push_back(state);
	gameStates.back()->onEnter();
}

void GameStateMachine::popState()
{
	if (!gameStates.empty())
	{
		if (gameStates.back()->onExit())
		{
			delete gameStates.back();
			gameStates.pop_back();
		}
	}
}

void GameStateMachine::changeState(GameState *state)
{
	if (!gameStates.empty())
	{
		if (gameStates.back()->getStateID() == state->getStateID())
		{
			return; // do nothing
		}
		if (gameStates.back()->onExit())
		{
			delete gameStates.back();
			gameStates.pop_back();
		}
	}
	// push back our new state
	gameStates.push_back(state);
	// initialise it
	gameStates.back()->onEnter();
}

void GameStateMachine::update()
{
	if (!gameStates.empty())
	{
		gameStates.back()->update();
	}
}

void GameStateMachine::render()
{
	if (!gameStates.empty())
	{
		gameStates.back()->render();
	}
}