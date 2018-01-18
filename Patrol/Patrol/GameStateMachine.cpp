#include "GameStateMachine.h"
#include <iostream>
#include "MenuState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "GameOverState.h"


GameStateMachine::GameStateMachine()
{
	int nextState = STATE_NULL;
	currentState = new MenuState();
}

void GameStateMachine::changeState()
{
	//If the state needs to be changed
	if (nextState != STATE_NULL)
	{
		//Delete the current state
		if (nextState != STATE_EXIT)
		{
			currentState->onExit();
			delete currentState;
		}//Change the state
		switch (nextState)
		{
		case STATE_MAIN_MENU:
			currentState = new MenuState();
			break;

		case STATE_PLAY:
			currentState = new PlayState();
			break;

		case STATE_PAUSE_MENU:
			currentState = new PauseState();
			break;

		case STATE_GAME_OVER:
			currentState = new GameOverState();
			break;
		}

		currentState->onEnter();

		//Change the current state ID
		stateID = nextState;

		//NULL the next state ID
		nextState = STATE_NULL;
	}
}

void GameStateMachine::set_next_state(int newState)
{
	//If the user doesn't want to exit
	if (nextState != STATE_EXIT)
	{
		//Set the next state
		nextState = newState;
	}
}

void GameStateMachine::update()
{
	if (currentState != 0)
	{
		currentState->update();
	}
}

void GameStateMachine::render()
{
	if (currentState != 0)
	{
		currentState->render();
	}
}