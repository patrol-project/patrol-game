#include "InputHandler.h"
#include "Game.h"
#include <iostream>

InputHandler* InputHandler::inputHandlerInstance = 0;

InputHandler::InputHandler() : keystates(0),
mousePosition(new Vector2D(0, 0))
{
	// create button states for the mouse
	for (int i = 0; i < 3; i++)
	{
		mouseButtonStates.push_back(false);
	}
}

InputHandler::~InputHandler()
{
	// delete anything we created dynamically
	delete keystates;
	delete mousePosition;

	// clear our arrays
	mouseButtonStates.clear();
}

void InputHandler::reset()
{
	mouseButtonStates[LEFT] = false;
	mouseButtonStates[RIGHT] = false;
	mouseButtonStates[MIDDLE] = false;
}

bool InputHandler::isKeyDown(SDL_Scancode key) const
{
	if (keystates != 0)
	{
		if (keystates[key] == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}

bool InputHandler::getMouseButtonState(int buttonNumber) const
{
	return mouseButtonStates[buttonNumber];
}

Vector2D* InputHandler::getMousePosition() const
{
	return mousePosition;
}

void InputHandler::update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			Game::Instance().quit();
			break;

		case SDL_MOUSEMOTION:
			onMouseMove(event);
			break;

		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonDown(event);
			break;

		case SDL_MOUSEBUTTONUP:
			onMouseButtonUp(event);
			break;

		case SDL_KEYDOWN:
			onKeyDown();
			break;

		case SDL_KEYUP:
			onKeyUp();
			break;

		default:
			break;
		}
	}
}

void InputHandler::onKeyDown()
{
	keystates = SDL_GetKeyboardState(0);
}

void InputHandler::onKeyUp()
{
	keystates = SDL_GetKeyboardState(0);
}

void InputHandler::onMouseMove(SDL_Event &event)
{
	mousePosition->setX(event.motion.x);
	mousePosition->setY(event.motion.y);
}

void InputHandler::onMouseButtonDown(SDL_Event &event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		mouseButtonStates[LEFT] = true;
	}

	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		mouseButtonStates[MIDDLE] = true;
	}

	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		mouseButtonStates[RIGHT] = true;
	}
}

void InputHandler::onMouseButtonUp(SDL_Event &event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		mouseButtonStates[LEFT] = false;
	}

	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		mouseButtonStates[MIDDLE] = false;
	}

	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		mouseButtonStates[RIGHT] = false;
	}
}
