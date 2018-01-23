#include "TileLayer.h"

TileLayer::TileLayer(int tileSize, const std::vector<Tileset>& tilesets) : m_tilesets(tilesets)
{
}

void TileLayer::update()
{
}

void TileLayer::render()
{
}

Tileset TileLayer::getTilesetByID(int tileID)
{
	return Tileset();
}
