#include "MenuButton.h"
#include "InputHandler.h"

MenuButton::MenuButton(const LoaderParams * params, void(*passedCallback)()):
	SDLGameObject(params), callback(passedCallback)
{
	currentFrame = MOUSE_OUT; // start at frame 0
}

void MenuButton::draw()
{
	SDLGameObject::draw(); // use the base class drawing
}

void MenuButton::update()
{
	Vector2D* mousePosition = InputHandler::Instance()->getMousePosition();

	if (mousePosition->getX() < (position.getX() + width)
		&& mousePosition->getX() > position.getX()
		&& mousePosition->getY() < (position.getY() + height)
		&& mousePosition->getY() > position.getY())
	{
		if (InputHandler::Instance()->getMouseButtonState(LEFT) && isReleased)
		{
			currentFrame = CLICKED;

			callback(); // calling the purpose of this button

			isReleased = false;
		}
		else if (!InputHandler::Instance()->getMouseButtonState(LEFT))
		{
			isReleased = true;
			currentFrame = MOUSE_OVER;
		}
	}
	else
	{
		currentFrame = MOUSE_OUT;
	}
}
void MenuButton::clean()
{
	SDLGameObject::clean();
}