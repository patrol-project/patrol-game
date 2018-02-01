#include "Player.h"
#include "Vector2D.h"
#include "InputHandler.h"
#include "BulletHandler.h"
#include "Game.h"
#include "TileLayer.h"
#include "SoundManager.h"
#include "Camera.h"
#include "TextureManager.h"

Player::Player() : PlayerObject(),
m_invulnerable(false),
m_invulnerableTime(200),
m_invulnerableCounter(0),
m_bPressedJump(false)
{
	m_jumpHeight = 80;
}

void Player::collision() {
	// if the player is not invulnerable then set to dying and change values for death animation tile sheet
	if (m_bDying && m_invulnerable)
	{
		m_currentFrame = 0;
		m_currentRow = 4;
		m_numFrames = 9;
		m_width = 50;
		m_bDying = true;

		std::cout << m_currentFrame;
	}
}

void Player::draw()
{
	if (m_bFlipped)
	{
		TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX() - Camera::Instance()->getPosition().getX(),
			(Uint32)m_position.getY() - Camera::Instance()->getPosition().getY(),
			m_width, m_height, m_currentRow, m_currentFrame, Game::Instance().getRenderer(), m_angle, m_alpha, SDL_FLIP_HORIZONTAL);
	}
	else
	{
		TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX() - Camera::Instance()->getPosition().getX(),
			(Uint32)m_position.getY() - Camera::Instance()->getPosition().getY(),
			m_width, m_height, m_currentRow, m_currentFrame, Game::Instance().getRenderer(), m_angle, m_alpha);
	}
}

void Player::load(std::unique_ptr<LoaderParams> const &pParams) {
	PlayerObject::load(std::move(pParams));    // inherited load function

											   // can set up the players inherited values here    
											   // set up bullets
	m_bulletFiringSpeed = 13;
	m_moveSpeed = 1;

	m_bulletCounter = m_bulletFiringSpeed;      // we want to be able to fire instantly

	m_dyingTime = 1;                          // time it takes for death explosion

	Camera::Instance()->setTarget(&m_position);
}


void Player::handleAnimation() {
	// if the player is invulnerable we can flash its alpha to let people know
	if (m_invulnerable)
	{
		// invulnerability is finished, set values back
		if (m_invulnerableCounter == m_invulnerableTime)
		{
			m_invulnerable = false;
			m_invulnerableCounter = 0;
			m_alpha = 255;
		}
		else // otherwise, flash the alpha on and off
		{
			if (m_alpha == 255)
			{
				m_alpha = 0;
			}
			else
			{
				m_alpha = 255;
			}
		}

		// increment our counter
		m_invulnerableCounter++;
	}

	if (!m_bDead && !m_bDying)
	{
		if (m_velocity.getY() < 0)
		{
			m_currentFrame = 2;
			m_currentRow = 2;
			m_numFrames = 2;
		}
		else if (m_velocity.getY() > 0)
		{
			m_currentRow = 3;
			m_numFrames = 1;
		}
		else
		{
			if (m_velocity.getX() < 0)
			{
				m_currentRow = 1;
				m_numFrames = 4;
				m_bFlipped = true;
			}
			else if (m_velocity.getX() > 0)
			{
				m_currentRow = 1;
				m_numFrames = 4;
				m_bFlipped = false;
			}
			else
			{
				m_currentRow = 0;
				m_numFrames = 1;
			}
		}

		if (m_bRunning)
		{
			m_currentFrame = int(((SDL_GetTicks() / (100)) % m_numFrames));
		}
		else
		{
			m_currentFrame = int(((SDL_GetTicks() / (120)) % m_numFrames));
		}

	}
	else
	{
		m_currentFrame = m_dyingCounter / m_numFrames;//int(((SDL_GetTicks() / (200)) % m_numFrames));
	}
	// if the player is not dead then we can change the angle with the velocity 
	// to give the impression of a moving helicopter
	/*if (!m_bDead) {
	if (m_velocity.getX() < 0) {
	m_angle = -10.0;
	}
	else if (m_velocity.getX() > 0) {
	m_angle = 10.0;
	}
	else {
	m_angle = 0.0;
	}
	}*/

	// our standard animation code - for helicopter propellors
	//m_currentFrame = int(((SDL_GetTicks() / (100)) % m_numFrames));
}

void Player::update()
{
	if (!m_bDying)
	{
		if (m_position.getY() + m_height >= 470)
		{
			collision();
		}

		handleInput();

		if (m_bMoveLeft)
		{
			if (m_bRunning)
			{
				m_velocity.setX(-5);
			}
			else
			{
				m_velocity.setX(-2);
			}
		}
		else if (m_bMoveRight)
		{
			if (m_bRunning)
			{
				m_velocity.setX(5);
			}
			else
			{
				m_velocity.setX(2);
			}
		}
		else
		{
			m_velocity.setX(0);
		}

		if (m_position.getY() < m_lastSafePos.getY() - m_jumpHeight)
		{
			m_bJumping = false;
		}

		if (!m_bJumping)
		{
			m_velocity.setY(5);
		}
		else
		{
			m_velocity.setY(-5);
		}

		handleMovement(m_velocity);
	}
	else
	{
		m_velocity.setX(0);
		if (m_dyingCounter == m_dyingTime)
		{
			ressurect();
		}
		m_dyingCounter++;

		m_velocity.setY(5);
	}
	handleAnimation();

}

void Player::handleMovement(Vector2D velocity)
{
	// get the current position
	Vector2D newPos = m_position;

	// add velocity to the x position
	newPos.setX(m_position.getX() + velocity.getX());

	// check if the new x position would collide with a tile
	if (!checkCollideTile(newPos))
	{
		// no collision, add to the actual x position
		m_position.setX(newPos.getX());
	}
	else
	{
		// collision, stop x movement
		m_velocity.setX(0);
	}

	// get the current position after x movement
	newPos = m_position;

	// add velocity to y position
	newPos.setY(newPos.getY() + velocity.getY());

	// check if new y position would collide with a tile
	if (!checkCollideTile(newPos))
	{
		// no collision, add to the actual x position
		m_position.setY(newPos.getY());
	}
	else
	{
		// collision, stop y movement
		m_velocity.setY(0);

		//  we collided with the map which means we are safe on the ground,
		//  make this the last safe position
		m_lastSafePos = m_position;

		// move the safe pos slightly back or forward so when resurrected we are safely on the ground after a fall
		if (velocity.getX() > 0)
		{
			m_lastSafePos.setX(m_lastSafePos.getX() - 32);
		}
		else if (velocity.getX() < 0)
		{
			m_lastSafePos.setX(m_lastSafePos.getX() + 32);

		}

		// allow the player to jump again
		m_bCanJump = true;

		// jumping is now false
		m_bJumping = false;
	}
}

void Player::ressurect() {
	Game::Instance().setPlayerLives(Game::Instance().getPlayerLives() - 1);

	m_position.setX(10);
	m_position.setY(200);
	m_bDying = false;

	//m_textureID = "player";

	m_currentFrame = 0;
	/*m_numFrames = 5;
	m_width = 101;
	m_height = 46;*/

	m_dyingCounter = 0;
	m_invulnerable = true;
}

void Player::clean() { PlayerObject::clean(); }

void Player::handleInput()
{
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT) && m_position.getX() < ((*m_pCollisionLayers->begin())->getMapWidth() * 32))
	{
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A))
		{
			m_bRunning = true;
		}
		else
		{
			m_bRunning = false;
		}

		m_bMoveRight = true;
		m_bMoveLeft = false;
	}
	else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT) && m_position.getX() > 32)
	{
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A))
		{
			m_bRunning = true;
		}
		else
		{
			m_bRunning = false;
		}

		m_bMoveRight = false;
		m_bMoveLeft = true;
	}
	else
	{
		m_bMoveRight = false;
		m_bMoveLeft = false;
	}

	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) && m_bCanJump && !m_bPressedJump)
	{
		SoundManager::Instance()->playSound("jump", 0);
		if (!m_bPressedJump)
		{
			m_bJumping = true;
			m_bCanJump = false;
			m_lastSafePos = m_position;
			m_bPressedJump = true;
		}
	}

	if (!InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) && m_bCanJump)
	{
		m_bPressedJump = false;
	}
}