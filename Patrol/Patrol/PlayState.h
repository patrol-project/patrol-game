#pragma once

#include "GameState.h"

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
};
