#include "Collider.h"
#include "AbstractGameObject.h"
#include "PhysicsManager.h"
#include <iostream>

Collider::Collider(std::string name) : AbstractComponent(name, AbstractComponent::Physics) {
	std::cout << "Collider created: " << name << std::endl;
}

Collider::~Collider() {
	std::cout << "Collider destroyed: " << this->getName() << std::endl;
	clearCollisions();
}


void Collider::setCollisionListener(CollisionListener* listener) {
	this->listener = listener;
}

bool Collider::hasCollisionWith(Collider* collider) {
	return this->collisions.find(collider) != this->collisions.end();
}

bool Collider::willCollide(Collider* another) {
	sf::FloatRect A = this->getGlobalBounds();
	sf::FloatRect B = another->getGlobalBounds();
	bool collision = A.intersects(B);
	return collision;
}



void Collider::addCollision(Collider* collider) {
	this->collisions.insert(collider);
}

void Collider::removeCollision(Collider* collider) {
	this->collisions.erase(collider);
}

void Collider::setLocalBounds(sf::FloatRect localBounds) {
	this->localBounds = localBounds;
}

void Collider::collisionEnter(AbstractGameObject* gameObjects) {
	if (this->listener) {
		this->listener->onCollisionEnter(gameObjects);
	}
}

void Collider::collisionExit(AbstractGameObject* gameObjects) {
	if (this->listener) {
		this->listener->onCollisionExit(gameObjects);
	}
}

sf::FloatRect Collider::getGlobalBounds() {
	return this->getOwner()->getGlobalTransform().transformRect(this->localBounds);
}

sf::FloatRect Collider::getLocalBounds() { 
	return this->localBounds;
}

void Collider::clearCollisions() {
	for (Collider* collider : this->collisions) {
		collider->collisionExit(this->getOwner());
		this->collisionExit(collider->getOwner());
		collider->removeCollision(this);	
	}
	collisions.clear();
}

void Collider::perform() {

}
