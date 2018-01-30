#pragma once

#include "SDL.h"
#include "GameStateMachine.h"

/**
 * @brief 
 * 
 */
class Game
{
public:
	/**
	* @brief Game::init initializes SDL and GameStateMachine and prepares everything for starting the game
	* 
	* @param title the title of the game window
	* @param xpos position on the X axis on screen
	* @param ypos position on the Y axis on screen
	* @param width width of the game window
	* @param height height of the game window
	* @param showWindow if we want to show the window when everything is ready
	* @return true if all SDL specific systems are properly initialised
	* @return false if any of the SDL systems failed to load properly
	*/
	bool init(const char* title, int xpos, int ypos, int width, int height, bool showWindow);
	
	/**
	 * @brief Listens for input and delegates the work to the InputHandler class 
	 * 
	 */
	void handleInput();

	/**
	 * @brief Uses TextureManager to load all the needed pictures for the game to start
	 * 
	 * @return true if everything loaded successfully
	 * @return false if some of the media couldn't load
	 */
	bool loadMedia();

	/**
	 * @brief Responsible for updating the game every frame. Delegates the work to the GameStateMachine class. 
	 * 
	 */
	void update();

	/**
	 * @brief Destroys all the loaded images, closes the window and quits SDL
	 * 
	 */
	void clean();

	/**
	 * @brief Stops the game loop.
	 * 
	 */
	void quit();
	
	/**
	 * @brief Responsible for drawing all the game objects to the screen. Delegates the work to GameStateMachine class. 
	 * 
	 */
	void render();

	/**
	 * @brief Returns the status of the game loop
	 * 
	 * @return true if the game is running
	 * @return false if the game is stopped
	 */
	bool get_running() const;

	/**
	 * @brief Returns the SDL renderer
	 * 
	 * @return SDL_Renderer* getRenderer 
	 */
	SDL_Renderer* getRenderer() const { return renderer; }

	/**
	 * @brief Returns the current game state from GameStateMachine
	 * 
	 * @return GameStateMachine* getStateMachine 
	 */
	GameStateMachine* getStateMachine() const { return gameStateMachine; }

	int getGameWidth() const
	{
		return m_gameWidth;
	}
	int getGameHeight() const
	{
		return m_gameHeight;
	}

	float getScrollSpeed()
	{
		return m_scrollSpeed;
	}

	void setPlayerLives(int lives);
	int getPlayerLives();

	void setCurrentLevel(int currentLevel);
	const int getCurrentLevel();

	void setNextLevel(int nextLevel);
	const int getNextLevel();

	void setLevelComplete(bool levelComplete);
	const bool getLevelComplete();

	bool changingState();
	void changingState(bool cs);

	std::vector<std::string> getLevelFiles();

	/**
	 * @brief Game class is following the Singleton pattern and Instance()
	 * is returning the only instance of the class if it is already created and
	 * if it is not created, creates it and returns it.
	 *
	 * @return Game& reference to the Game instance
	 */
	static Game& Instance()
	{
		static Game instance;

		return instance;
	}

	Game(Game const&) = delete;
	void operator=(Game const&) = delete;
private:
	Game() {}///< private constructor to ensure no one creates second instance of this class

	bool running; ///< used to control the game loop
	int m_gameWidth;
	int m_gameHeight;

	float m_scrollSpeed;
	SDL_Window* window; ///< reference to the SDL window object
	SDL_Renderer* renderer; ///< reference to the SDL renderer
	SDL_Texture* texture; 

	bool m_bChangingState;
	int m_playerLives;

	int m_currentLevel;
	int m_nextLevel;
	bool m_bLevelComplete;

	std::vector<std::string> m_levelFiles;

	GameStateMachine* gameStateMachine; ///< reference to the GameStateMachine object which controls the game states
};
