#pragma once

#include "GameState.h"
#include "GameObject.h"
#include <vector>

class PauseState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual string getStateID() const { return pauseID; }
private:
	static void pauseToMain();
	static void resumePlay();
	static const string pauseID;
	vector<GameObject*> gameObjects;
};