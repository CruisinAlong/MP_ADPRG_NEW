#pragma once
#include "AbstractPoolable.h"
#include "AbstractGameObject.h"
#include "CollisionListener.h"
#include "ObjectPoolHolder.h"
#include "PhysicsManager.h"
#include "UIManager.h" 
#include "UIData.h" 

class EnemyAirplane : public AbstractPoolable , public CollisionListener {
public:
	EnemyAirplane(std::string name);
	void initialize();

	void onRelease();
	void onActivate();
	AbstractPoolable* clone();

	void onCollisionEnter(AbstractGameObject* gameObjects);
	void onCollisionExit(AbstractGameObject* gameObjects);
private:
	sf::Sprite* sprite = new sf::Sprite();
	int counter = 0;

	const int SPAWN_RANGE = 300.f;
	bool collisionProcessed = false;
	Collider* collider;
};