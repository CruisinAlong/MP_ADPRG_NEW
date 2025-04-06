#include "PhysicsManager.h"
#include <iostream>

PhysicsManager* PhysicsManager::sharedInstance = nullptr;


void PhysicsManager::initialize(std::string name, AbstractGameObject* parent) {
    if (sharedInstance == nullptr) {
        sharedInstance = new PhysicsManager(name);
        parent->attachComponent(sharedInstance);
        std::cout << "PhysicsManager initialized." << std::endl;
    }
    else {
        std::cout << "PhysicsManager already initialized." << std::endl;
    }
}


PhysicsManager* PhysicsManager::getInstance() {
    return sharedInstance;
}

void PhysicsManager::trackObject(Collider* object) {
    if (object == nullptr) {
        std::cerr << "Error: Attempted to track a null collider." << std::endl;
        return;
    }

    if (object->getOwner() == nullptr) {
        std::cerr << "Error: Collider has no owner." << std::endl;
        return;
    }
    trackedObjects.reserve(1);


    this->trackedObjects.push_back(object);


}




void PhysicsManager::untrackObject(Collider* object) {

    this->forCleaningObjects.push_back(object);
    this->CleanUpObjects();

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

                    }
                    if (!this->trackedObjects[j]->hasCollisionWith(this->trackedObjects[i])) 
                    {
                        this->trackedObjects[j]->addCollision(this->trackedObjects[i]);
                        this->trackedObjects[j]->collisionEnter(this->trackedObjects[i]->getOwner());
                    }
                } 
                else {
                    if (this->trackedObjects[i]->hasCollisionWith(this->trackedObjects[j])) {
                        this->trackedObjects[i]->collisionExit(this->trackedObjects[j]->getOwner());
                        this->trackedObjects[i]->removeCollision(this->trackedObjects[j]);

                    }
                    if (this->trackedObjects[j]->hasCollisionWith(this->trackedObjects[i])) {
                        this->trackedObjects[j]->collisionExit(this->trackedObjects[i]->getOwner());
                        this->trackedObjects[j]->removeCollision(this->trackedObjects[i]);

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
