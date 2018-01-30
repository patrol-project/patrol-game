#include "PlayerObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "TileLayer.h"

PlayerObject::PlayerObject() : GameObject(),
m_bulletFiringSpeed(0),
m_bulletCounter(0),
m_moveSpeed(0),
m_dyingTime(0),
m_dyingCounter(0),
m_bPlayedDeathSound(false),
m_bFlipped(false),
m_bMoveLeft(false),
m_bMoveRight(false),
m_bRunning(false),
m_bFalling(false),
m_bJumping(false),
m_bCanJump(false),
m_lastSafePos(0, 0)
{
}

void PlayerObject::load(std::unique_ptr<LoaderParams> const &pParams)
{
	// get position
	m_position = Vector2D(pParams->getX(), pParams->getY());

	// get drawing variables
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();
	m_numFrames = pParams->getNumberOfFrames();
}

// draw the object to the screen
void PlayerObject::draw()
{
	TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(),
		m_width, m_height, m_currentRow, m_currentFrame, Game::Instance().getRenderer(), m_angle, m_alpha);
}

// apply velocity to current position
void PlayerObject::update()
{
	m_position += m_velocity;
	m_currentFrame = int(((SDL_GetTicks() / (1000 / 3)) % m_numFrames));
}

void PlayerObject::doDyingAnimation()
{
	m_currentFrame = int(((SDL_GetTicks() / (1000 / 10)) % m_numFrames));

	if (m_dyingCounter == m_dyingTime)
	{
		m_bDead = true;
	}
	m_dyingCounter++;
}

bool PlayerObject::checkCollideTile(Vector2D newPos)
{
	if (newPos.getY() + m_height >= Game::Instance().getGameHeight() - 32)
	{
		return false;
	}
	else
	{
		for (std::vector<TileLayer*>::iterator it = m_pCollisionLayers->begin(); it != m_pCollisionLayers->end(); ++it)
		{
			TileLayer* pTileLayer = (*it);
			std::vector<std::vector<int>> tiles = pTileLayer->getTileIDs();

			Vector2D layerPos = pTileLayer->getPosition();

			int x, y, tileColumn, tileRow, tileid = 0;

			x = layerPos.getX() / pTileLayer->getTileSize();
			y = layerPos.getY() / pTileLayer->getTileSize();

			Vector2D startPos = newPos;
			startPos.setX(startPos.getX() + 15);
			startPos.setY(startPos.getY() + 20);
			Vector2D endPos(newPos.getX() + (m_width - 15), (newPos.getY()) + m_height - 4);

			for (int i = startPos.getX(); i < endPos.getX(); i++)
			{
				for (int j = startPos.getY(); j < endPos.getY(); j++)
				{
					tileColumn = i / pTileLayer->getTileSize();
					tileRow = j / pTileLayer->getTileSize();

					tileid = tiles[tileRow + y][tileColumn + x];

					if (tileid != 0)
					{
						return true;
					}
				}
			}
		}

		return false;
	}
}