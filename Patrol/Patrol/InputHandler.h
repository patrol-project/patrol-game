#pragma once

#include <iostream>
#include <vector>

#include <SDL.h>
#include "Vector2D.h"

using namespace std;

/**
 * @brief Easier to use this enum than only numbers.Needed for SDL InputHandler methods.
 * 
 */
enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

/**
 * @brief Responsible for listening to input and it's handling.
 * Singleton approach.
 * 
 */
class InputHandler
{
public:

	/**
	 * @brief Get a reference to the only instance of this class
	 * 
	 * @return InputHandler* 
	 */
	static InputHandler* Instance()
	{
		if (inputHandlerInstance == 0)
		{
			inputHandlerInstance = new InputHandler();
		}

		return inputHandlerInstance;
	}

	/**
	 * @brief Polls for events from SDL. Then using a switch-case based on the event
	 * decides which function to call next and what to do.
	 * 
	 */
	void update();

	void clean();

	/**
	 * @brief Sets all mouse button states to false.
	 * 
	 */
	void reset();

	/**
	 * @brief Given a SDL_Scancode(all of which can be found on SDL site documentation)
	 * checks if the given key is pressed or not
	 * 
	 * @param key code for a key on the keyboard
	 * @return true if the key is pressed
	 * @return false if the key is not pressed
	 */
	bool isKeyDown(SDL_Scancode key) const;

	/**
	 * @brief Using the mouse_buttons enum we can check the
	 * state of every mouse button
	 * 
	 * @param buttonNumber 0,1,2 for left, middle, right
	 * @return true if pressed
	 * @return false if not pressed
	 */
	bool getMouseButtonState(int buttonNumber) const;

	/**
	 * @brief Returns the position of the mouse 
	 * 
	 * @return Vector2D* X and Y position of the mouse
	 */
	Vector2D* getMousePosition() const;

private:

	InputHandler();
	~InputHandler();

	InputHandler(const InputHandler&);
	InputHandler& operator=(const InputHandler&);

	/**
	 * @brief Handles when a key on the keyboard is pressed
	 * 
	 */
	void onKeyDown();

	/**
	 * @brief Handles when a key on the keyboard is released
	 * 
	 */
	void onKeyUp();

	/**
	 * @brief Changes mouse position X and Y values
	 * 
	 * @param event 
	 */
	void onMouseMove(SDL_Event& event);

	/**
	 * @brief When a mouse button is pressed changes the corresponding
	 * value in mouseButtonStates to true
	 * 
	 * @param event 
	 */
	void onMouseButtonDown(SDL_Event& event);

	/**
	 * @brief When a mouse button is released changes the corresponding 
	 * value in mouseButtonStates to false
	 * 
	 * @param event 
	 */
	void onMouseButtonUp(SDL_Event& event);

	// keyboard specific
	const Uint8* keystates;

	// mouse specific
	vector<bool> mouseButtonStates; ///< Keeps LEFT,MIDDLE,RIGHT button states to true or false if pressed or not
	Vector2D* mousePosition; ///< Keeps where is the mouse on the screen

	// singleton
	static InputHandler* inputHandlerInstance; 
};
