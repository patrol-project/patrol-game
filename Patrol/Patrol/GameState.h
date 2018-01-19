#pragma once

#include<string>
#include <vector>

using namespace std;

/**
* @brief Abstract base class with pure virtual functions which serves as a
* blueprint for all Game states.
*
*/
class GameState
{
public:
	virtual ~GameState() {}
	/**
	* @brief Updating game objects every frame
	*
	*/
	virtual void update() = 0;

	/**
	* @brief Draws to the screen all the game object every frame
	*
	*/
	virtual void render() = 0;

	/**
	* @brief Loads all needed stuff for the game state
	*
	* @return true if everything is ok
	* @return false if something fails
	*/
	virtual bool onEnter() = 0;

	/**
	* @brief Free all resources and clean after it
	*
	* @return true
	* @return false
	*/
	virtual bool onExit() = 0;

	/**
	* @brief Every game state has it's own ID
	*
	* @return string getStateID
	*/
	virtual string getStateID() const = 0;

protected:

	GameState() : m_loadingComplete(false), m_exiting(false)
	{

	}

	bool m_loadingComplete;
	bool m_exiting;

	std::vector<std::string> m_textureIDList;

};