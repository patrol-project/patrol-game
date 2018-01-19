#pragma once

#include <iostream>
#include <vector>
#include "tinyxml2.h"

class GameObject;
class StateParser
{
public:

	StateParser() {}
	~StateParser() {}

	bool parseState(const char* stateFile, std::string stateID, std::vector<GameObject*> *pObjects, std::vector<std::string> *pTextureIDs);

private:

	void parseObjects(tinyxml2::XMLElement* pStateRoot, std::vector<GameObject*> *pObjects);
	void parseTextures(tinyxml2::XMLElement* pStateRoot, std::vector<std::string> *pTextureIDs);
};

