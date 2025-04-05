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
    if (object && object->getOwner()) {
        std::cout << "Tracking object: " << object->getName() << std::endl;
        this->trackedObjects.push_back(object);
    }
    else {
        std::cout << "Error: Attempted to track an invalid object or object with no owner." << std::endl;
    }
}


void PhysicsManager::untrackObject(Collider* object) {
    std::cout << "Scheduled for cleanup: " << object->getName() << std::endl;
    this->forCleaningObjects.push_back(object);
    this->CleanUpObjects();
    std::cout << "Performing PhysicsManager cleanup." << std::endl;
    this->printTrackedObjects();
}

void PhysicsManager::perform() {
    for (int i = 0; i < this->trackedObjects.size(); i++) {
        for (int j = 0; j < this->trackedObjects.size(); j++) {
            if (this->trackedObjects[i]->getOwner()->isEnabled() &&
                this->trackedObjects[j]->getOwner()->isEnabled()) {

                if (this->trackedObjects[i]->willCollide(this->trackedObjects[j])) {

                    if (!this->trackedObjects[i]->hasCollisionWith(this->trackedObjects[j])) 
                    {
                        this->trackedObjects[i]->addCollision(this->trackedObjects[j]);
                        this->trackedObjects[i]->collisionEnter(this->trackedObjects[j]->getOwner());
                        std::cout << this->trackedObjects[i]->getName() << " collisionEnter with " 
                                  << this->trackedObjects[j]->getName() << std::endl;
                    }
                    if (!this->trackedObjects[j]->hasCollisionWith(this->trackedObjects[i])) 
                    {
                        this->trackedObjects[j]->addCollision(this->trackedObjects[i]);
                        this->trackedObjects[j]->collisionEnter(this->trackedObjects[i]->getOwner());
                    }
                } 
                else
                {

                } {
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

}

void PhysicsManager::printTrackedObjects() {
    std::cout << "Current tracked objects:" << std::endl;
    for (const auto& obj : trackedObjects) {
        std::cout << " - " << obj->getName() << std::endl;
    }
}

void PhysicsManager::CleanUpObjects() {
    for (int i = 0; i < this->forCleaningObjects.size(); i++) {
        for (int j = 0; j < this->trackedObjects.size(); j++) {
            if (this->forCleaningObjects[i] == this->trackedObjects[j]) {
                std::cout << "Removing object: " << this->trackedObjects[j]->getName() << " from tracked objects." << std::endl;
                this->trackedObjects.erase(this->trackedObjects.begin() + j);
            }
        }
    }
    this->forCleaningObjects.clear();
	std::cout << "Size of tracked objects: " << this->trackedObjects.size() << std::endl;
	std::cout << "Size of forCleaningObjects: " << this->forCleaningObjects.size() << std::endl;
}
