#pragma once

#include "MenuState.h"
#include "GameObject.h"
#include <vector>
#include "StateParser.h"

class GameOverState : public MenuState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual string getStateID() const { return gameOverID; }
private:
	virtual void setCallbacks(const std::vector<Callback>& callbacks);
	static void gameOverToMain();
	static void restartPlay();
	static const string gameOverID;
	vector<GameObject*> gameObjects;
};