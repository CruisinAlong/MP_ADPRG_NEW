// BallObject.cpp
#include "BallObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "Renderer.h"
#include "BallMovement.h"
#include <iostream>

BallObject::BallObject(std::string name) : AbstractPoolable(name), CollisionListener(), isMoving(false) {
}

BallObject::~BallObject() {
    delete this->sprite;
}

void BallObject::initialize() {
    this->sprite = new sf::Sprite();
    sprite->setTexture(*TextureManager::getInstance()->getTexture("avenger"));
    sf::Vector2u textureSize = sprite->getTexture()->getSize();
    sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

    this->setPosition(rand() % Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT - static_cast<int>(textureSize.y) / 2);

    Renderer* renderer = new Renderer("BallSprite");
    renderer->assignDrawable(sprite);
    this->attachComponent(renderer);

    this->collider = new Collider("BallCollider");
    this->collider->setLocalBounds(sprite->getGlobalBounds());
    this->collider->setCollisionListener(this);
    this->attachComponent(this->collider);

    BallMovement* movement = new BallMovement("BallMovement");
    this->attachComponent(movement);

    std::cout << "BallObject initialized" << std::endl;
}

void BallObject::onRelease() {
    isMoving = false;
    PhysicsManager::getInstance()->untrackObject(this->collider);
}

void BallObject::onActivate() {
    PhysicsManager::getInstance()->trackObject(this->collider);
}

AbstractPoolable* BallObject::clone() {
    return new BallObject(this->name);
}

void BallObject::onCollisionEnter(AbstractGameObject* contact) {
    if (contact->getName().find("PlayerObject") != std::string::npos) {
        std::cout << "BallObject collided with PlayerObject" << std::endl;
        isMoving = true;
    }
}

void BallObject::onCollisionExit(AbstractGameObject* gameObject) {
    // Handle collision exit if needed
}
