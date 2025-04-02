#pragma once
#include <SFML/System.hpp>
#include <string>

class AbstractGameObject;

class AbstractComponent {
public:
	enum ComponentType { NotSet = -1, Script = 0, Renderer = 1, Input = 2, Physics = 3};
	AbstractComponent(std::string name, ComponentType type);
	virtual ~AbstractComponent();

	void attachOwner(AbstractGameObject* owner);
	void detachOwner();
	AbstractGameObject* getOwner();
	ComponentType getType();
	std::string getName();

	void setDeltaTime(sf::Time deltaTime);
	virtual void perform() = 0;
protected:
	AbstractGameObject* owner;
	ComponentType type;
	std::string name;
	sf::Time deltaTime;
};