#pragma once

#include "GameState.h"
#include "GameObject.h"
#include <vector>

class GameOverState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual string getStateID() const { return gameOverID; }
private:
	static void gameOverToMain();
	static void restartPlay();
	static const string gameOverID;
	vector<GameObject*> gameObjects;
};