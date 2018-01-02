#pragma once

#include "GameState.h"
#include <vector>

class GameStateMachine
{
public:
	void pushState(GameState* state);
	void changeState(GameState* state);
	void popState();
	void update();
	void render();
private:
	vector<GameState*> gameStates;
};
