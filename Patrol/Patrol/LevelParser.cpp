#include <string>
#include "LevelParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "ObjectLayer.h"
#include "TileLayer.h"
#include "GameObjectFactory.h"
#include "base64.h"
#include "Level.h"

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

	//we know that properties is the first child of the root
	tinyxml2::XMLElement* pProperties = pRoot->FirstChildElement();

	// we must parse the textures needed for this level, which have been added to properties
	for (tinyxml2::XMLElement* e = pProperties->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("property"))
		{
			parseTextures(e);
		}
	}

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
		if (e->Value() == std::string("objectgroup") || e->Value() == std::string("layer"))
		{
			if (e->FirstChildElement()->Value() == std::string("object"))
			{
				parseObjectLayer(e, pLevel->getLayers(), pLevel);
			}
			else if (e->FirstChildElement()->Value() == std::string("data"))
			{
				parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets());
			}
		}
	}

	return pLevel;
}

void LevelParser::parseTextures(tinyxml2::XMLElement* pTextureRoot)
{
	string resourcesPath = "Resources/";
	TextureManager::Instance()->load(
		resourcesPath.append(pTextureRoot->Attribute("value")),
		pTextureRoot->Attribute("name"),
		Game::Instance().getRenderer()
	);
}

void LevelParser::parseObjectLayer(tinyxml2::XMLElement * pObjectElement, std::vector<Layer*>* pLayers, Level* pLevel)
{
	// create an object layer
	ObjectLayer* pObjectLayer = new ObjectLayer();
	std::cout << pObjectElement->FirstChildElement()->Value();
	for (tinyxml2::XMLElement* e = pObjectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		std::cout << e->Value();
		if (e->Value() == std::string("object"))
		{
			int x, y, width, height, numFrames, callbackID, animSpeed;
			x = y = width = height = numFrames = callbackID = animSpeed = 0;
			std::string textureID;
			std::string type;
			// get the initial node values type, x and y
			x = e->IntAttribute("x");
			y = e->IntAttribute("y");

			type = e->Attribute("type");
			GameObject* pGameObject = GameObjectFactory::Instance()->create(type);
			// get the property values
			for (tinyxml2::XMLElement* properties = e->FirstChildElement(); properties != NULL; properties = properties->NextSiblingElement())
			{
				if (properties->Value() == std::string("properties"))
				{
					for (tinyxml2::XMLElement* property = properties->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
					{
						if (property->Value() == std::string("property"))
						{
							if (property->Attribute("name") == std::string("numFrames"))
							{
								numFrames = property->IntAttribute("value");
							}
							else if (property->Attribute("name") == std::string("textureHeight"))
							{
								height = property->IntAttribute("value");
							}
							else if (property->Attribute("name") == std::string("textureID"))
							{
								textureID = property->Attribute("value");
							}
							else if (property->Attribute("name") == std::string("textureWidth"))
							{
								width = property->IntAttribute("value");
							}
							else if (property->Attribute("name") == std::string("callbackID"))
							{
								callbackID = property->IntAttribute("value");
							}
							else if (e->Attribute("name") == std::string("animSpeed"))
							{
								animSpeed = property->IntAttribute("value");
							}
						}
					}
				}
			}
			pGameObject->load(std::unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed)));
			if (type == "Player")
			{
				pLevel->setPlayer(dynamic_cast<Player*>(pGameObject));
			}

			pObjectLayer->getGameObjects()->push_back(pGameObject);
		}
	}
	pLayers->push_back(pObjectLayer);
}


void LevelParser::parseTilesets(tinyxml2::XMLElement* pTilesetRoot, std::vector<Tileset>* pTilesets)
{
	std::string resourcePath = "Resources/";
	string q = resourcePath.append(pTilesetRoot->FirstChildElement()->Attribute("source"));
	// first add the tileset to texture manager
	TextureManager::Instance()->load(
		resourcePath.append(pTilesetRoot->FirstChildElement()->Attribute("source")),
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
		//	First you need to base64 - decode it, then you may need to decompress it.
		//	Now you have an array of bytes, which should be interpreted as an
		//	array of unsigned 32 - bit integers using little - endian byte ordering.
		decodedIDs = base64_decode(t);
	}

	std::vector<int> layerRow(m_width);

	for (int j = 0; j < m_height; j++)
	{
		data.push_back(layerRow);
	}
	int index = 0;
	for (int rows = 0; rows < m_height; rows++)
	{
		for (int cols = 0; cols < m_width; cols++)
		{
			// decodedIDs is a byte array where every 4 char represent int32 using little-endian byte ordering
			// that's why we shift every char accordingly 
			// https://stackoverflow.com/questions/17916394/converting-4-bytes-in-little-endian-order-into-an-unsigned-integer
			uint32_t a = decodedIDs[index] | decodedIDs[index + 1] << 8 | decodedIDs[index + 2] << 16 | decodedIDs[index + 3] << 24;
			data[rows][cols] = a;
			index += 4;
		}
		cout << endl;
	}
	pTileLayer->setTileIDs(data);
	pTileLayer->setMapWidth(m_width);

	pLayers->push_back(pTileLayer);
}

