#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"
#include "Player.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "Enemy.h"
#include "GameOverState.h"
#include "StateParser.h"
#include "BulletHandler.h"

const string PlayState::playId = "PLAY";

void PlayState::update()
{
	if (m_loadingComplete && !m_exiting)
	{
		if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
		{
			Game::Instance().getStateMachine()->set_next_state(STATE_PAUSE_MENU);
		}

		BulletHandler::Instance()->updateBullets();

		if (Game::Instance().getPlayerLives() == 0)
		{
			Game::Instance().getStateMachine()->set_next_state(STATE_GAME_OVER);
		}

		if (pLevel != 0)
		{
			pLevel->update();
		}
	}
}

void PlayState::render()
{
	if (m_loadingComplete)
	{
		if (pLevel != 0)
		{
			pLevel->render();
		}

		for (int i = 0; i < Game::Instance().getPlayerLives(); i++)
		{
			TextureManager::Instance()->drawFrame("lives", i * 32, 0, 32, 32, 0, 0, Game::Instance().getRenderer(), 0.0, 255);
		}

		BulletHandler::Instance()->drawBullets();
	}
}

bool PlayState::onEnter()
{
	//LevelParser levelParser;
	//pLevel = levelParser.parseLevel("tiles.tmx");

	//	parse the state
	//	StateParser stateParser;
	//	stateParser.parseState("States.xml", playId, &gameObjects, &m_textureIDList);
	//	std::cout << "entering PlayState\n";
	//return true;

	// new

	Game::Instance().setPlayerLives(3);

	LevelParser levelParser;
	pLevel = levelParser.parseLevel(Game::Instance().getLevelFiles()[Game::Instance().getCurrentLevel() - 1].c_str());
	//pLevel = levelParser.parseLevel("Resources/Level2.tmx");

	TextureManager::Instance()->load("Resources/GameObjects/missle.png", "missle", Game::Instance().getRenderer());
	TextureManager::Instance()->load("Resources/GameObjects/bullet1.png", "bullet1", Game::Instance().getRenderer());
	TextureManager::Instance()->load("Resources/GameObjects/bullet2.png", "bullet2", Game::Instance().getRenderer());
	TextureManager::Instance()->load("Resources/GameObjects/bullet3.png", "bullet3", Game::Instance().getRenderer());
	TextureManager::Instance()->load("Resources/GameObjects/lives.png", "lives", Game::Instance().getRenderer());
	TextureManager::Instance()->load("Resources/GameObjects/largeexplosion.png", "largeexplosion", Game::Instance().getRenderer());

	Mix_ResumeMusic();

	if (pLevel != 0)
	{
		m_loadingComplete = true;
	}

	std::cout << "entering PlayState\n";
	startTime = SDL_GetTicks();
	return true;
}

bool PlayState::onExit()
{
	endTime = SDL_GetTicks();
	Game::Instance().setLatestResult(endTime-startTime);
	//m_exiting = true;

	InputHandler::Instance()->reset();
	BulletHandler::Instance()->clearBullets();

	Mix_PauseMusic();

	std::cout << "exiting PlayState\n";
	return true;
}