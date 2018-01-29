#include "MenuButton.h"
#include "InputHandler.h"

MenuButton::MenuButton() : PlayerObject(), m_callback(0), isReleased(true)
{
}

void MenuButton::load(std::unique_ptr<LoaderParams> const &pParams)
{
	PlayerObject::load(std::move(pParams));
	callbackID = pParams->getCallbackID();
	m_currentFrame = MOUSE_OUT;
}

void MenuButton::draw()
{
	PlayerObject::draw(); // use the base class drawing
}

void MenuButton::update()
{
	Vector2D* mousePosition = InputHandler::Instance()->getMousePosition();

	if (mousePosition->getX() < (m_position.getX() + m_width)
		&& mousePosition->getX() > m_position.getX()
		&& mousePosition->getY() < (m_position.getY() + m_height)
		&& mousePosition->getY() > m_position.getY())
	{
		if (InputHandler::Instance()->getMouseButtonState(LEFT) && isReleased)
		{
			m_currentFrame = CLICKED;

			m_callback(); // calling the purpose of this button

			isReleased = false;
		}
		else if (!InputHandler::Instance()->getMouseButtonState(LEFT))
		{
			isReleased = true;
			m_currentFrame = MOUSE_OVER;
		}
	}
	else
	{
		m_currentFrame = MOUSE_OUT;
	}
}
void MenuButton::clean()
{
	PlayerObject::clean();
}