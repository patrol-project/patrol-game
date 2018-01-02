#pragma once

#include"GameState.h"

class MenuState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual string getStateID() const { return menuId; }
private:
	static const string menuId;
};
