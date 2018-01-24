#include "GameStateMachine.h"
#include <iostream>
#include "MainMenuState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "GameOverState.h"

GameStateMachine::GameStateMachine()
{
	int nextState = STATE_NULL;
	gameStatesMap[STATE_MAIN_MENU] = new MainMenuState();
	gameStatesMap[STATE_PAUSE_MENU] = new PauseState();
	gameStatesMap[STATE_GAME_OVER] = new GameOverState();
	gameStatesMap[STATE_PLAY] = new PlayState();
}

void GameStateMachine::changeState()
{
	//If the state needs to be changed
	if (nextState != STATE_NULL)
	{
		//Delete the current state
		if (nextState != STATE_EXIT && currentState != 0)
		{
			currentState->onExit();
			//delete currentState;
		}

		//Change the state
		switch (nextState)
		{
		case STATE_MAIN_MENU:
			currentState = gameStatesMap[STATE_MAIN_MENU];
			break;

		case STATE_PLAY:
			currentState = gameStatesMap[STATE_PLAY];
			break;

		case STATE_PAUSE_MENU:
			currentState = gameStatesMap[STATE_PAUSE_MENU];
			break;

		case STATE_GAME_OVER:
			currentState = gameStatesMap[STATE_GAME_OVER];
			break;
		case STATE_RESET_GAME:
			gameStatesMap[STATE_PLAY]->onExit();
			delete gameStatesMap[STATE_PLAY];
			gameStatesMap[STATE_PLAY] = new PlayState();
			currentState = gameStatesMap[STATE_MAIN_MENU];
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