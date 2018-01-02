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
	Vector2D position;
	Vector2D velocity;
	Vector2D acceleration;
	int width;
	int height;
	int currentRow;
	int currentFrame;
	string textureID;
};
