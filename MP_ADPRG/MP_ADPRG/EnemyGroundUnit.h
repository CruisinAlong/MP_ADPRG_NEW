#pragma once

#include "AbstractPoolable.h"
#include "CollisionListener.h"
#include "Renderer.h"
#include "EnemyBehavior.h"
#include "Collider.h"

class EnemyGroundUnit : public AbstractPoolable, public CollisionListener {
public:
    EnemyGroundUnit(std::string name);
    ~EnemyGroundUnit();

    void initialize() override;
    void onRelease() override;
    void onActivate() override;
    AbstractPoolable* clone() override;

    void onCollisionEnter(AbstractGameObject* contact) override;
    void onCollisionExit(AbstractGameObject* gameObject) override;

private:
    sf::Sprite* sprite;
    Collider* collider;
    const int SPAWN_RANGE = 300;
};


