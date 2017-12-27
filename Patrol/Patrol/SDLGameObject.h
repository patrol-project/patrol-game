#pragma once

#include "GameObject.h"
#include "LoaderParams.h"
#include <string>
#include "SDL.h"
#include "Vector2D.h"

using namespace std;

class SDLGameObject : public GameObject
{
public:
	SDLGameObject(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
protected:
	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;
	int m_width;
	int m_height;
	int m_currentRow;
	int m_currentFrame;
	string m_textureID;
};
