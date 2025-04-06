// FastJumpingEnemy.h
#pragma once
#include "AbstractPoolable.h"
#include "CollisionListener.h"
#include "EnemyBehavior.h"
#include "Collider.h"
#include <SFML/Graphics.hpp>

class FastJumpingEnemy : public AbstractPoolable, public CollisionListener {
public:
    FastJumpingEnemy(std::string name);
    void initialize() override;
    void onRelease() override;
    void onActivate() override;
    void update(sf::Time deltaTime) override;
    void onCollisionEnter(AbstractGameObject* contact) override;
    void onCollisionExit(AbstractGameObject* gameObject) override;
    AbstractPoolable* clone() override;

private:
    sf::Sprite* sprite; 
    Collider* collider;
    bool hasJumped;
    bool collisionProcessed = false;
};



