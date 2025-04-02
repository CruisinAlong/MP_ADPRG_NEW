#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "AbstractComponent.h"
#include "GenericInputController.h"
#include "Renderer.h"

class AbstractGameObject
{
public:
	AbstractGameObject(std::string name);
	virtual ~AbstractGameObject();
	virtual void initialize() = 0;
	virtual void processInputs(sf::Event event);
	virtual void update(sf::Time deltaTime);
	virtual void draw(sf::RenderWindow* window, sf::RenderStates renderStates);
	std::string getName();

	void attachComponent(AbstractComponent* component);
	void detachComponent(AbstractComponent* component);
	void attachChild(AbstractGameObject* child);
	void detachChild(AbstractGameObject* child);
	AbstractComponent* findComponentByName(std::string name);
	AbstractComponent* findComponentOfType(AbstractComponent::ComponentType type, std::string name);
	AbstractGameObject* getParent();
	std::vector<AbstractComponent*> getComponentsOfType(AbstractComponent::ComponentType type);
	std::vector<AbstractComponent*> getComponentsOfTypeRecursive(AbstractComponent::ComponentType type);
	sf::Transformable* getTransformable();
	sf::Transform getGlobalTransform(); 
	void setPosition(float x, float y);
	void setEnabled(bool flag);
	bool isEnabled();
protected:
	sf::Transformable transformable;
	std::string name;
	sf::Sprite* sprite;
	sf::Texture* texture;
	std::vector<AbstractGameObject*> childList;
	std::vector<AbstractComponent*> componentList;
	void setParent(AbstractGameObject* gameObject);
private:
	/*std::vector<AbstractComponent*> getComponentsRecursiveProper(
		AbstractGameObject* object, AbstractComponent::ComponentType type,
		std::vector<AbstractComponent*> foundList);*/
	bool enabled = true;
	AbstractGameObject* mParent;
};