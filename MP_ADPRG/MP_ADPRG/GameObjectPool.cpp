#include "GameObjectPool.h"
#include "GameObjectManager.h"
#include <iostream>

GameObjectPool::GameObjectPool(std::string tag, AbstractPoolable* poolableCopy, int poolableSize, AbstractGameObject* parent) {
    this->tag = tag;
    this->objectCopy = poolableCopy;
    this->maxPoolSize = poolableSize;
    this->parent = parent;
}

GameObjectPool::~GameObjectPool() {
    delete this->objectCopy;
    this->objectCopy = nullptr;
    this->parent = nullptr;
}

void GameObjectPool::initialize() {
    for (int i = 0; i < this->maxPoolSize; i++) {
        AbstractPoolable* poolableObject = this->objectCopy->clone();

        if (this->parent != nullptr) {
            this->parent->attachChild(poolableObject);
        }
        else {
            GameObjectManager::getInstance()->addObject(poolableObject);
        }

        poolableObject->setEnabled(false);
        this->availableObjects.push_back(poolableObject);
    }
}

bool GameObjectPool::hasObjectAvailable(int requestSize) {
    return requestSize <= this->availableObjects.size();
}

AbstractPoolable* GameObjectPool::requestPoolable() {
    if (this->hasObjectAvailable(1)) {
        AbstractPoolable* poolableObject = this->availableObjects.back();
        this->availableObjects.pop_back();
        this->usedObjects.push_back(poolableObject);
        

        this->setEnabled(poolableObject, true);
        return poolableObject;
    }
    else {

        return nullptr;
    }
}

std::vector<AbstractPoolable*> GameObjectPool::requestPoolableBatch(int size) {
    std::vector<AbstractPoolable*> returnList;
    if (this->hasObjectAvailable(size)) {
        for (int i = 0; i < size; i++) {
            returnList.push_back(this->requestPoolable());
        }
    }
    else {

    }
    return returnList;
}

std::string GameObjectPool::getTag() {
    return this->tag;
}

void GameObjectPool::setEnabled(AbstractPoolable* poolableObject, bool flag) {
    if (flag) {
        poolableObject->setEnabled(true);
        poolableObject->onActivate();
    }
    else {
        poolableObject->setEnabled(false);
        poolableObject->onRelease();
    }
}

void GameObjectPool::releasePoolable(AbstractPoolable* poolableObject) {
    auto it = std::find(this->usedObjects.begin(), this->usedObjects.end(), poolableObject);
    if (it != this->usedObjects.end()) {
        this->usedObjects.erase(it);
        this->availableObjects.push_back(poolableObject);
        this->setEnabled(poolableObject, false);
    }
}

void GameObjectPool::releasePoolableBatch(std::vector<AbstractPoolable*> objectList) {
    for (auto& poolableObject : objectList) {
        this->releasePoolable(poolableObject);
    }
}

std::vector<AbstractPoolable*> GameObjectPool::getUsedObjects() {
    return this->usedObjects;
}





