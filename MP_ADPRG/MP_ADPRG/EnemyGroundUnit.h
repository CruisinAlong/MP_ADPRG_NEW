#pragma once

#include "AbstractPoolable.h"
#include "CollisionListener.h"
#include "Renderer.h"
#include "EnemyBehavior.h"
#include "Collider.h"
#include "UIManager.h"

class EnemyGroundUnit : public AbstractPoolable, public CollisionListener {
public:
    EnemyGroundUnit(std::string name);

    void initialize() override;
    void onRelease() override;
    void onActivate() override;
	void update(sf::Time deltaTime) override; 
    AbstractPoolable* clone() override;

    void onCollisionEnter(AbstractGameObject* contact) override;
    void onCollisionExit(AbstractGameObject* gameObject) override;

private:
    sf::Sprite* sprite;
    Collider* collider;
    int nextId;
    int id;
    const int SPAWN_RANGE = 300;
};


