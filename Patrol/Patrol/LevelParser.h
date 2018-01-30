#pragma once

#include "tinyxml2.h"
#include <iostream>
#include <vector>

class Level;
struct Tileset;
class Layer;
class TileLayer;

class LevelParser
{
public:
	Level * parseLevel(const char* stateFile);
private:
	void parseTilesets(tinyxml2::XMLElement* pTilesetRoot, std::vector<Tileset>* pTilesets);
	void parseTileLayer(tinyxml2::XMLElement* pTileElement, std::vector<Layer*> *pLayers, const std::vector<Tileset>* pTilesets, std::vector<TileLayer*> *pCollisionLayers);
	void parseTextures(tinyxml2::XMLElement* pTextureRoot);
	void parseObjectLayer(tinyxml2::XMLElement* pObjectElement, std::vector<Layer*> *pLayers, Level* pLevel);
	int m_tileSize;
	int m_width;
	int m_height;
};
