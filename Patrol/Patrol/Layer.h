#pragma once

class Level;

class Layer
{
public:

	virtual ~Layer() {}

	virtual void render() = 0;
	virtual void update(Level* pLevel) = 0;
};
