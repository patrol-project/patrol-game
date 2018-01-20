#pragma once

#include <iostream>
#include <vector>
#include "Layer.h"
//#include "LevelParser.h"
#include "Player.h"
//#include "CollisionManager.h"

class TileLayer;

struct Tileset
{
	int firstGridID;
	int tileWidth;
	int tileHeight;
	int spacing;
	int margin;
	int width;
	int height;
	int numColumns;
	std::string name;
};

class Level
{
public:

	void update();
	void render();

private:
	friend class LevelParser;
	Level() {}

	std::vector<Tileset> m_tilesets;
	std::vector<Tileset>* getTilesets() { return &m_tilesets; }

	std::vector<Layer*> m_layers;
	std::vector<Layer*>* getLayers() { return &m_layers; }
};