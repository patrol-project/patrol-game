#include "MenuButton.h"
#include "InputHandler.h"

MenuButton::MenuButton(const LoaderParams* params) :
	SDLGameObject(params)
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
		currentFrame = MOUSE_OVER;
		if (InputHandler::Instance()->getMouseButtonState(LEFT))
		{
			currentFrame = CLICKED;
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