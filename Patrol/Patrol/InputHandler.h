#pragma once

#include <iostream>
#include <vector>

#include <SDL.h>
#include "Vector2D.h"

using namespace std;

enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputHandler
{
public:

	static InputHandler* Instance()
	{
		if (inputHandlerInstance == 0)
		{
			inputHandlerInstance = new InputHandler();
		}

		return inputHandlerInstance;
	}

	// update and clean the input handler
	void update();
	void clean();

	// keyboard events
	bool isKeyDown(SDL_Scancode key) const;

	// mouse events
	bool getMouseButtonState(int buttonNumber) const;
	Vector2D* getMousePosition() const;

private:

	InputHandler();
	~InputHandler();

	void reset();

	InputHandler(const InputHandler&);
	InputHandler& operator=(const InputHandler&);

	// handle keyboard events
	void onKeyDown();
	void onKeyUp();

	// handle mouse events
	void onMouseMove(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);

	// keyboard specific
	const Uint8* keystates;

	// mouse specific
	vector<bool> mouseButtonStates;
	Vector2D* mousePosition;

	// singleton
	static InputHandler* inputHandlerInstance;
};
