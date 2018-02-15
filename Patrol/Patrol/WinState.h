#pragma once

#include "MenuState.h"
#include "GameObject.h"
#include <vector>
#include "StateParser.h"

class WinState : public MenuState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual string getStateID() const { return winID; }
private:
	virtual void setCallbacks(const std::vector<Callback>& callbacks);
	static void gameOverToMain();
	static void nextLevel();
	static const string winID;
	vector<GameObject*> gameObjects;
};