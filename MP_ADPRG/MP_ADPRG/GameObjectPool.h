#pragma once
#include "AbstractPoolable.h"
#include <vector>

class GameObjectPool {
public:
	GameObjectPool(std::string, AbstractPoolable* poolableCopy, int poolableSize, AbstractGameObject* parent);
	~GameObjectPool();
	void initialize();
	bool hasObjectAvailable(int requestSize);
	AbstractPoolable* requestPoolable();
	std::vector<AbstractPoolable*> requestPoolableBatch(int size);

	void releasePoolable(AbstractPoolable* poolableObject);
	void releasePoolableBatch(std::vector<AbstractPoolable*> objectList);

	std::string getTag();
	std::vector<AbstractPoolable*> getUsedObjects();
private:
	std::string tag;
	AbstractPoolable* objectCopy = NULL;
	AbstractGameObject* parent = NULL;
	int maxPoolSize = 20;
	std::vector<AbstractPoolable*> availableObjects;
	std::vector<AbstractPoolable*> usedObjects;

	void setEnabled(AbstractPoolable* poolableObject, bool flag);
};