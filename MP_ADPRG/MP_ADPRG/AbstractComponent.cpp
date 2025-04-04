#include "AbstractComponent.h"

AbstractComponent::AbstractComponent(std::string name, ComponentType type) {
	this->name = name;
	this->owner = nullptr;
	this->type = type;
}

AbstractComponent::~AbstractComponent() {
	this->owner = nullptr;
	this->type = NotSet;
}

AbstractGameObject* AbstractComponent::getOwner() {
	return this->owner;
}

AbstractComponent::ComponentType AbstractComponent::getType() {
	return this->type;
}

std::string AbstractComponent::getName() {
	return this->name;
}

void AbstractComponent::setDeltaTime(sf::Time deltaTime) {
	this->deltaTime = deltaTime;
}

void AbstractComponent::attachOwner(AbstractGameObject* object) {
	this->owner = object;
}

void AbstractComponent::detachOwner() {
	delete this;
}

