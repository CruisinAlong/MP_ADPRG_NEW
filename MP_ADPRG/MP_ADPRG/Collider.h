#pragma once
#include "AbstractComponent.h"
#include "CollisionListener.h"
#include "AbstractGameObject.h"
#include "TextureManager.h"
#include <unordered_set>

class Collider : public AbstractComponent
{
public:

	Collider(std::string name);
	~Collider();
	void setCollisionListener(CollisionListener* listener);



	bool willCollide(Collider* another);
	bool hasCollisionWith(Collider* collider);
	void addCollision(Collider* collider);
	void removeCollision(Collider* collider);

	sf::FloatRect getGlobalBounds();
	sf::FloatRect getLocalBounds(); 
	void setLocalBounds(sf::FloatRect bounds);
	void collisionEnter(AbstractGameObject* gameObjects);
	void collisionExit(AbstractGameObject* gameObjects);

	void perform();
	void clearCollisions();
	sf::Sprite& getDebugSprite();
private:

	bool checked = false;

	std::unordered_set<Collider*> collisions;
	sf::FloatRect localBounds;
	CollisionListener* listener;

};