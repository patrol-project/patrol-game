#pragma once

#include "PlayerObject.h"

class Enemy : public PlayerObject
{
public:
	virtual std::string type();

protected:
	int m_health;

	Enemy();
	virtual ~Enemy();
};