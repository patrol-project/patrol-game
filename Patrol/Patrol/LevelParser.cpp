#include "LevelParser.h"

Level* LevelParser::parseLevel(const char *levelFile)
{
	// create a TinyXML document and load the map XML
	tinyxml2::XMLDocument levelDocument;
	levelDocument.LoadFile(levelFile);
	// create the level object
	Level* pLevel = new Level();
	// get the root node
	tinyxml2::XMLElement* pRoot = levelDocument.RootElement();
	m_tileSize = pRoot->IntAttribute("tilewidth");
	m_width = pRoot->IntAttribute("width");
	m_height = pRoot->IntAttribute("height");

	// parse the tilesets
	for (tinyxml2::XMLElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("tileset"))
		{
			parseTilesets(e, pLevel->getTilesets());
		}
	}

	// parse any object layers
	for (tinyxml2::XMLElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("layer"))
		{
			parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets());
		}
	}

	return pLevel;
}


void LevelParser::parseTilesets(tinyxml2::XMLElement* pTilesetRoot, std::vector<Tileset>* pTilesets)
{
	// first add the tileset to texture manager
	TextureManager::Instance()->load(
		pTilesetRoot->FirstChildElement()->Attribute("source"),
		pTilesetRoot->Attribute("name"),
		Game::Instance().getRenderer()
	);

	// create a tileset object
	Tileset tileset;
	tileset.width = pTilesetRoot->FirstChildElement()->IntAttribute("width");
	tileset.height = pTilesetRoot->FirstChildElement()->IntAttribute("height");
	tileset.firstGridID = pTilesetRoot->IntAttribute("firstgid");
	tileset.tileWidth = pTilesetRoot->IntAttribute("tilewidth");
	tileset.tileHeight = pTilesetRoot->IntAttribute("tileheight");
	tileset.spacing = pTilesetRoot->IntAttribute("spacing");
	tileset.margin = pTilesetRoot->IntAttribute("margin");
	tileset.name = pTilesetRoot->Attribute("name");
	tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);

	pTilesets->push_back(tileset);
}

void LevelParser::parseTileLayer(tinyxml2::XMLElement* pTileElement, std::vector<Layer*> *pLayers, const std::vector<Tileset>* pTilesets)
{
	TileLayer* pTileLayer = new TileLayer(m_tileSize, *pTilesets);
	// tile data
	std::vector<std::vector<int>> data;
	std::string decodedIDs;
	tinyxml2::XMLElement* pDataNode = nullptr;

	for (tinyxml2::XMLElement* e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("data"))
		{
			pDataNode = e;
		}
	}

	for (tinyxml2::XMLNode* e = pDataNode->FirstChild(); e != NULL; e = e->NextSibling())
	{
		tinyxml2::XMLText* text = e->ToText();
		std::string t = text->Value();
		decodedIDs = base64_decode(t);
	}

	std::vector<int> layerRow(m_width);

	for (int j = 0; j < m_height; j++)
	{
		data.push_back(layerRow);
	}

	for (int rows = 0; rows < m_height; rows++)
	{
		for (int cols = 0; cols < m_width; cols++)
		{
			data[rows][cols] = decodedIDs[rows * m_width + cols];
		}
	}
	pTileLayer->setTileIDs(data);
	pLayers->push_back(pTileLayer);
}