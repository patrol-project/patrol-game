#include "StateParser.h"

#include "StateParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameObjectFactory.h"
#include <memory>


using namespace std;

bool StateParser::parseState(const char *stateFile, string stateID, vector<GameObject *> *pObjects, std::vector<std::string> *pTextureIDs)
{
	// create the XML document
	tinyxml2::XMLDocument xmlDoc;

	// load the state file
	if (xmlDoc.LoadFile(stateFile) != tinyxml2::XML_SUCCESS)
	{
		xmlDoc.PrintError();
		return false;
	}

	// get the root element
	tinyxml2::XMLElement* pRoot = xmlDoc.RootElement();

	// pre declare the states root node
	tinyxml2::XMLElement* pStateRoot = 0;
	// get this states root node and assing it to pStateRoot
	for (auto e = pRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == stateID)
		{
			pStateRoot = e;
			break;
		}
	}

	// pre declare the texture root
	tinyxml2::XMLElement* pTextureRoot = 0;

	// get the root of the texture elements
	for (auto e = pStateRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == string("TEXTURES"))
		{
			pTextureRoot = e;
			break;
		}
	}

	// now parse the textures
	parseTextures(pTextureRoot, pTextureIDs);

	// pre declare the object root node
	tinyxml2::XMLElement* pObjectRoot = 0;

	// get the root node and assign it to pObjectRoot
	for (auto e = pStateRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == string("OBJECTS"))
		{
			pObjectRoot = e;
			break;
		}
	}

	// now parse the objects
	parseObjects(pObjectRoot, pObjects);

	return true;
}

void StateParser::parseTextures(tinyxml2::XMLElement* pStateRoot, std::vector<std::string> *pTextureIDs)
{
	// for each texture we get the filename and the desired ID and add them to the texture manager
	for (auto e = pStateRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		string filenameAttribute = e->Attribute("filename");
		string idAttribute = e->Attribute("ID");

		pTextureIDs->push_back(idAttribute); // push the id into the list

		TextureManager::Instance()->load(filenameAttribute, idAttribute, Game::Instance().getRenderer());
	}
}

void StateParser::parseObjects(tinyxml2::XMLElement *pStateRoot, std::vector<GameObject *> *pObjects)
{
	for (auto e = pStateRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		int callbackID = e->IntAttribute("callbackID");
		int x = e->IntAttribute("x");
		int y = e->IntAttribute("y");
		int width = e->IntAttribute("width");
		int height = e->IntAttribute("height");
		int numFrames = e->IntAttribute("numFrames");
		int animSpeed = e->IntAttribute("animSpeed");
		string textureID = e->Attribute("textureID");
		//int x, int y, int width, int height, std::string textureID, int numFrames, void()
		GameObject* pGameObject = GameObjectFactory::Instance()->create(e->Attribute("type"));
		pGameObject->load(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed));
		pObjects->push_back(pGameObject);
	}
}