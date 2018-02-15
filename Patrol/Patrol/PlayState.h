#pragma once

#include "GameState.h"
#include <vector>
#include "GameObject.h"
#include "Level.h"
#include "LevelParser.h"

class PlayState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual string getStateID() const { return playId; }
private:
	static const string playId;
	vector<GameObject*> gameObjects;
	Level* pLevel;
	int startTime;
	int endTime;
};
