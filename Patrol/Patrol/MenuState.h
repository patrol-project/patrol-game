#pragma once

#include "GameState.h"
#include "GameObject.h"
#include <vector>

/**
* @brief In this state the menu is showed on the screen with corresponding game object on it.
*
*/
class MenuState : public GameState
{
public:

	virtual ~MenuState() {}

protected:

	typedef void(*Callback)();
	virtual void setCallbacks(const std::vector<Callback>& callbacks) = 0;

	std::vector<Callback> m_callbacks;
};
