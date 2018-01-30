#pragma once

#include "PlayerObject.h"
#include "GameObjectFactory.h"
#include "SoundManager.h"
#include "Game.h"

class Player : public PlayerObject
{
public:
	Player();
	virtual ~Player() {}

	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void load(std::unique_ptr<LoaderParams> const &pParams);

	virtual void collision();

	virtual std::string type() { return "Player"; }

private:
	void ressurect();       // bring the player back if there are lives left        
	void handleInput();     // handle any input from the keyboard, mouse, or joystick        
	void handleAnimation(); // handle any animation for the player

							//handle player movement
	void handleMovement(Vector2D velocity); 

							// player can be invulnerable for a time
	int m_invulnerable;
	int m_invulnerableTime;
	int m_invulnerableCounter;

	bool m_bPressedJump;
};

// for the factory
class PlayerCreator : public BaseCreator 
{
	GameObject* createGameObject() const { return new Player(); }
};