#include "AbstractGameObject.h"
#include "AbstractComponent.h"
#include "GenericInputController.h"
#include <iostream>

AbstractGameObject::AbstractGameObject(std::string name)
    : name(name), sprite(nullptr), texture(nullptr) // Initialize member variables
{

}

AbstractGameObject::~AbstractGameObject()
{
    if (this->sprite != nullptr) {
        delete this->sprite;
    }
	for (int i = 0; i < this->componentList.size(); i++) {
        if (this->componentList[i] != nullptr) {
            delete this->componentList[i];
        }
	}
	for (int i = 0; i < this->childList.size(); i++) {
		delete this->childList[i];
	}

}

std::string AbstractGameObject::getName()
{
    return name;
}

void AbstractGameObject::draw(sf::RenderWindow* window, sf::RenderStates renderStates)
{
    renderStates.transform = renderStates.transform * this->transformable.getTransform();

    std::vector<AbstractComponent*> componentList = this->getComponentsOfType(AbstractComponent::ComponentType::Renderer);

    for (int j = 0; j < componentList.size(); j++) {
        Renderer* renderer = (Renderer*)componentList[j];
        renderer->assignTargetWindow(window);
        renderer->setRenderStates(renderStates);
        renderer->perform();
    }
    for (int i = 0; i < this->childList.size(); i++) {
        AbstractGameObject* child = this->childList[i];
        child->draw(window, renderStates);
    }
}

void AbstractGameObject::processInputs(sf::Event event) {

    if (!this->isEnabled()) return;

    std::vector<AbstractComponent*> componentList = this->getComponentsOfType(AbstractComponent::ComponentType::Input);
    for (int j = 0; j < componentList.size(); j++) {
        ((GenericInputController*)componentList[j])->assignEvent(event);
        componentList[j]->perform();
    }

    for (int i = 0; i < childList.size(); i++) {
        childList[i]->processInputs(event);
    }
}

void AbstractGameObject::setPosition(float x, float y)
{
    this->transformable.setPosition(x, y);

}



void AbstractGameObject::update(sf::Time deltaTime) {
    std::vector<AbstractComponent*> componentList =
        this->getComponentsOfType(AbstractComponent::ComponentType::Script);

    for (int j = 0; j < componentList.size(); j++) {
        componentList[j]->setDeltaTime(deltaTime);
        componentList[j]->perform();
    }

    for (int i = 0; i < this->childList.size(); i++) {

        childList[i]->update(deltaTime);
    }
}

void AbstractGameObject::attachComponent(AbstractComponent* component) {
    this->componentList.push_back(component);
    component->attachOwner(this);
    std::cout << "Attached component: " << component->getName() << " of type " << component->getType() << " to game object: " << this->name << std::endl; // Debug log
}

void AbstractGameObject::detachComponent(AbstractComponent* component) {
    int index = -1;
    for (int i = 0; i < this->componentList.size(); i++) {
        if (this->componentList[i] == component) {
            index = i;
            this->componentList[i]->detachOwner();
            break;
        }
    }

    if (index != -1) {
        this->componentList.erase(this->componentList.begin() + index);

    }
}

AbstractComponent* AbstractGameObject::findComponentByName(std::string name) {
    for (int i = 0; i < this->componentList.size(); i++) {
        if (this->componentList[i]->getName() == name) {
            return this->componentList[i];
        }
    }
    return NULL;
}

AbstractComponent* AbstractGameObject::findComponentOfType(AbstractComponent::ComponentType type, std::string name) {
    for (int i = 0; i < this->componentList.size(); i++) {
        if (this->componentList[i]->getName() == name && this->componentList[i]->getType() == type) {
            return this->componentList[i];
        }
    }
    return NULL;
}

std::vector<AbstractComponent*> AbstractGameObject::getComponentsOfType(AbstractComponent::ComponentType type) {
    std::vector<AbstractComponent*> foundList;
    for (int i = 0; i < this->componentList.size(); i++) {
        if (this->componentList[i]->getType() == type) {
            foundList.push_back(this->componentList[i]);
        }
    }
    return foundList;
}

void AbstractGameObject::attachChild(AbstractGameObject* child)
{
    this->childList.push_back(child);
    child->setParent(this);
    child->initialize();

}

void AbstractGameObject::detachChild(AbstractGameObject* child)
{
    int index = -1;
    for (int i = 0; i < this->childList.size(); i++)
    {
        if (this->childList[i] == child)
        {
            index = i;
        }
    }

    if (index != -1)
    {
        this->childList.erase(this->childList.begin() + index);
        this->childList.shrink_to_fit();

    }
}

sf::Transformable* AbstractGameObject::getTransformable() {
    return &this->transformable;
}

void AbstractGameObject::setEnabled(bool flag) {
    this->enabled = flag;
}

bool AbstractGameObject::isEnabled() {
    return this->enabled;
}

AbstractGameObject* AbstractGameObject::getParent() {
    return this->mParent;
}

void AbstractGameObject::setParent(AbstractGameObject* parent) {
    this->mParent = parent;
}

sf::Transform AbstractGameObject::getGlobalTransform() {
    AbstractGameObject* parentObj = this;
    std::vector<AbstractGameObject*> parentList;
    while (parentObj != NULL) {
        parentList.push_back(parentObj);
        parentObj = parentObj->getParent();
    }
    sf::Transform transform = sf::Transform::Identity;
    int startIdx = parentList.size() - 1;
    for (int i = startIdx; i >= 0; i--) {
        transform = transform * parentList[i]->getTransformable()->getTransform();
    }
    return transform;
}

sf::RenderWindow* AbstractGameObject::getRenderWindow() {
    if (mParent) {
        return mParent->getRenderWindow();
    }
    return nullptr;
}

AbstractComponent* AbstractGameObject::getComponentByName(const std::string& name) {
    for (AbstractComponent* component : componentList) {
        if (component->getName() == name) {
            return component;
        }
    }
    return nullptr;
}