#pragma once
#include "AbstractGameObject.h"
#include "Collider.h"
#include <unordered_map>
#include <iostream>

class GameObjectManager
{
public:
	static GameObjectManager* getInstance();
	void TestFunction();
	AbstractGameObject* findObjectByName(std::string name);
	std::vector<AbstractGameObject*> getAllObjects();
	int activeObjects();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow* window);
	void addObject(AbstractGameObject* object);
	void deleteObject(AbstractGameObject* gameObject);
	void deleteObjectByName(std::string name);
	void deleteAllObjectsInScene();
private:
	GameObjectManager();
	GameObjectManager(GameObjectManager const&) {};
	GameObjectManager& operator=(GameObjectManager const&) {};
	static GameObjectManager* sharedInstance;
	
	std::unordered_map<std::string, AbstractGameObject*> mGameObject;
	std::vector<AbstractGameObject*> mGameObjectList;
};