#include "GameObjectManager.h"

GameObjectManager* GameObjectManager::sharedInstance = nullptr;

GameObjectManager::GameObjectManager()
{
	std::cout << "GameObjectManager constructor called" << std::endl;
};

GameObjectManager* GameObjectManager::getInstance()
{
	if (sharedInstance == nullptr) {
		sharedInstance = new GameObjectManager();
	}
	return sharedInstance;
};

AbstractGameObject* GameObjectManager::findObjectByName(std::string name)
{
	if (mGameObject[name] != nullptr) {
		return mGameObject[name];
	}
	else {
		std::cerr << "Object not found" << std::endl;
		return nullptr;
	}
};

std::vector<AbstractGameObject*> GameObjectManager::getAllObjects()
{
	return mGameObjectList;
};

int GameObjectManager::activeObjects()
{
	return mGameObjectList.size();
};

void GameObjectManager::processInput(sf::Event event)
{
	for (int i = 0; i < mGameObjectList.size(); i++)
	{
		mGameObjectList[i]->processInputs(event);
	}
};

void GameObjectManager::update(sf::Time deltaTime)
{
	for (int i = 0; i < mGameObjectList.size(); i++)
	{
		mGameObjectList[i]->update(deltaTime);
	}
};

void GameObjectManager::draw(sf::RenderWindow* window)
{
	for (int i = 0; i < mGameObjectList.size(); i++)
	{
		if (mGameObjectList[i]->isEnabled())
		{
			mGameObjectList[i]->draw(window, sf::RenderStates::Default);
		}
	}
}


void GameObjectManager::addObject(AbstractGameObject* object)
{
	mGameObject[object->getName()] = object;
	mGameObjectList.push_back(object);
	object->initialize();
};

void GameObjectManager::deleteObject(AbstractGameObject* gameObject)
{
	std::string key = gameObject->getName();
	delete gameObject;
	mGameObject.erase(key);
	mGameObjectList.erase(std::remove(mGameObjectList.begin(), mGameObjectList.end(), gameObject));
	mGameObjectList.shrink_to_fit();
};

void GameObjectManager::deleteObjectByName(std::string name)
{
	AbstractGameObject* gameObject = findObjectByName(name);
	if (gameObject != nullptr) {
		deleteObject(gameObject);
	}

};

void GameObjectManager::deleteAllObjectsInScene() {
	std::cout << "Deleting all objects in scene" << std::endl;
	for (int i = 0; i < mGameObjectList.size(); i++) {
		std::cout << "Deleting object: " << mGameObjectList[i]->getName() << std::endl;
		delete mGameObjectList[i];
	}
	mGameObjectList.clear();
	mGameObjectList.shrink_to_fit();
	mGameObject.clear();
	std::cout << "All objects deleted in scene" << std::endl;
}
