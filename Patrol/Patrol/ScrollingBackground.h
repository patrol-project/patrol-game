#pragma once

#include <iostream>
#include "GameObjectFactory.h"
#include "PlayerObject.h"

class ScrollingBackground : public PlayerObject
{
public:

	virtual ~ScrollingBackground() {}
	ScrollingBackground();

	virtual void draw();
	virtual void update();
	virtual void clean();

	virtual void load(std::unique_ptr<LoaderParams> const &pParams);

private:

	int m_scrollSpeed;

	int count;
	int maxcount;

	SDL_Rect m_srcRect1;
	SDL_Rect m_srcRect2;

	SDL_Rect m_destRect1;
	SDL_Rect m_destRect2;

	int m_srcRect1Width;
	int m_srcRect2Width;

	int m_destRect1Width;
	int m_destRect2Width;
};

class ScrollingBackgroundCreator : public BaseCreator
{
public:

	virtual GameObject* createGameObject() const
	{
		return new ScrollingBackground();
	}
};