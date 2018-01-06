#pragma once

#include "SDLGameObject.h"

/**
 * @brief Game object which is a button in the game
 * 
 */
class MenuButton : public SDLGameObject
{
public:
	/**
	 * @brief Constructor accepting two arguments
	 * 
	 * @param params All needed parameters for initiliazing a game object
	 * @param callback Function pointer to a function which will execute when the button is pressed
	 */
	MenuButton(const LoaderParams* params, void (*callback)());
	
	/**
	 * @brief Draw the button to the screen
	 * 
	 */
	virtual void draw();

	/**
	 * @brief Update button status if hovered or clicked.
	 * 
	 */
	virtual void update();

	/**
	 * @brief Free resources
	 * 
	 */
	virtual void clean();

private:
	/**
	 * @brief For easier understanding when a mouse is on the button, when click it and when is not on the button.
	 * 
	 */
	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2
	};

	/**
	 * @brief Keeps current button status. False if pressed, true if released.
	 * 
	 */
	bool isReleased;

	/**
	 * @brief Function pointer. Points to the function which will execute when the button is pressed.
	 * 
	 */
	void(*callback)();
};
