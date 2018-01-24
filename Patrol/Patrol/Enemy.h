#pragma once

#include "ShooterObject.h"

class Enemy : public ShooterObject
{
public:
	virtual std::string type();

protected:
	int m_health;

	Enemy();
	virtual ~Enemy();
};