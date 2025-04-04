#include "PhysicsManager.h"
#include <iostream>

PhysicsManager* PhysicsManager::sharedInstance = nullptr;

void PhysicsManager::initialize(std::string name, AbstractGameObject* parent) {
    sharedInstance = new PhysicsManager(name);
    parent->attachComponent(sharedInstance);
    std::cout << "PhysicsManager initialized." << std::endl;
}

PhysicsManager* PhysicsManager::getInstance() {
    return sharedInstance;
}

void PhysicsManager::trackObject(Collider* object) {
    this->trackedObjects.push_back(object);
    std::cout << "Tracking object: " << object->getName() << std::endl;
}

void PhysicsManager::untrackObject(Collider* object) {
    this->forCleaningObjects.push_back(object);
    std::cout << "Untracking object: " << object->getName() << std::endl;
}

void PhysicsManager::perform() {
    for (int i = 0; i < this->trackedObjects.size(); i++) {
        for (int j = i + 1; j < this->trackedObjects.size(); j++) {
            if (this->trackedObjects[i]->getOwner()->isEnabled() &&
                this->trackedObjects[j]->getOwner()->isEnabled()) {

                if (this->trackedObjects[i]->willCollide(this->trackedObjects[j])) {
                    std::cout << "Collision detected between " << this->trackedObjects[i]->getName()
                        << " and " << this->trackedObjects[j]->getName() << std::endl;

                    if (!this->trackedObjects[i]->hasCollisionWith(this->trackedObjects[j])) {
                        this->trackedObjects[i]->addCollision(this->trackedObjects[j]);
                        this->trackedObjects[i]->collisionEnter(this->trackedObjects[j]->getOwner());
                        std::cout << this->trackedObjects[i]->getName() << " collisionEnter with "
                            << this->trackedObjects[j]->getName() << std::endl;
                    }
                    if (!this->trackedObjects[j]->hasCollisionWith(this->trackedObjects[i])) {
                        this->trackedObjects[j]->addCollision(this->trackedObjects[i]);
                        this->trackedObjects[j]->collisionEnter(this->trackedObjects[i]->getOwner());
                        std::cout << this->trackedObjects[j]->getName() << " collisionEnter with "
                            << this->trackedObjects[i]->getName() << std::endl;
                    }
                }
                else {
                    if (this->trackedObjects[i]->hasCollisionWith(this->trackedObjects[j])) {
                        this->trackedObjects[i]->collisionExit(this->trackedObjects[j]->getOwner());
                        this->trackedObjects[i]->removeCollision(this->trackedObjects[j]);
                        std::cout << this->trackedObjects[i]->getName() << " collisionExit with "
                            << this->trackedObjects[j]->getName() << std::endl;
                    }
                    if (this->trackedObjects[j]->hasCollisionWith(this->trackedObjects[i])) {
                        this->trackedObjects[j]->collisionExit(this->trackedObjects[i]->getOwner());
                        this->trackedObjects[j]->removeCollision(this->trackedObjects[i]);
                        std::cout << this->trackedObjects[j]->getName() << " collisionExit with "
                            << this->trackedObjects[i]->getName() << std::endl;
                    }
                }
            }
        }
    }
    this->CleanUpObjects();
}

void PhysicsManager::CleanUpObjects() {
    for (int i = 0; i < this->forCleaningObjects.size(); i++) {
        for (int j = 0; j < this->trackedObjects.size(); j++) {
            if (this->forCleaningObjects[i] == this->trackedObjects[j]) {
                std::cout << "Cleaning up object: " << this->trackedObjects[j]->getName() << std::endl;
                this->trackedObjects.erase(this->trackedObjects.begin() + j);
            }
        }
    }
    this->forCleaningObjects.clear();
}
