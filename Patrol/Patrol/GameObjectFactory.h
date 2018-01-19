#pragma once

#include <string>
#include <map>
#include "GameObject.h"
#include <iostream>

class BaseCreator {

public:
	virtual GameObject* createGameObject() const = 0;
	virtual ~BaseCreator();
};

class GameObjectFactory {

public:
	static GameObjectFactory* Instance();

	bool registerType(std::string typeID, BaseCreator* pCreator);

	GameObject* create(std::string typeID);

private:

	GameObjectFactory();
	~GameObjectFactory();

	std::map<std::string, BaseCreator*> m_creators;

	static GameObjectFactory* pInstance;
};
