#include "Player.h"
#include "Vector2D.h"
#include "InputHandler.h"

Player::Player(const LoaderParams* pParams) :
	SDLGameObject(pParams)
{
}

void Player::draw()
{
	SDLGameObject::draw();
}

void Player::update()
{
	velocity.setX(0);
	velocity.setY(0);

	handleInput(); // add our function

	currentFrame = int(((SDL_GetTicks() / 100) % 1));
	
	SDLGameObject::update();
}

void Player::clean()
{
}

void Player::handleInput()
{
	Vector2D* target = InputHandler::Instance()->getMousePosition();
	velocity = *target - position;
	velocity /= 50;
}