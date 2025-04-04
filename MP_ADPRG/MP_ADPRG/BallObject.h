#pragma once
#include "AbstractPoolable.h"
#include "CollisionListener.h"
#include "Collider.h" 
#include "Renderer.h"
#include <iostream>
#include "TextureManager.h"
#include "Game.h"
#include <SFML/Graphics.hpp>

class BallObject : public AbstractPoolable, public CollisionListener {
public:
    BallObject(std::string name);
    ~BallObject();
    void initialize() override;
    void onRelease() override;
    void onActivate() override;
    void onCollisionEnter(AbstractGameObject* contact) override;
    void onCollisionExit(AbstractGameObject* gameObject) override;
    AbstractPoolable* clone() override;
    bool isMoving;
private:
    sf::Sprite* sprite;
    Collider* collider; 

};
