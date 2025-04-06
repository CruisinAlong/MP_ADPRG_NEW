#pragma once

#include "AbstractGameObject.h"
#include "CollisionListener.h"
#include "Collider.h"
#include "ObjectPoolHolder.h"
#include "PhysicsManager.h"
#include "UIManager.h" 
#include "UIData.h" 
#include <SFML/Graphics.hpp>
#include <iostream>

class BallPlayer : public AbstractGameObject, public CollisionListener {
public:
    BallPlayer(std::string name);
    void initialize() override;
    void processInputs(sf::Event event) override;
    void update(sf::Time deltaTime) override;
    void onCollisionEnter(AbstractGameObject* contact) override;
    void onCollisionExit(AbstractGameObject* gameObject) override;
    sf::Sprite* getSprite() const;
    bool isJumping() const; 


private:
    Collider* collider;
    sf::Sprite* sprite;
    bool isJumpingFlag;
    bool hasHitGround;
    static constexpr float GROUND_LEVEL = 450.0f;   
    bool isOnGround;
    bool collisionExited; 
};