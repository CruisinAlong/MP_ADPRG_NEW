// AirplanePlayer.cpp
#include "AirplanePlayer.h"
#include "Game.h"
#include "PlayerInputController.h"
#include "PlayerMovement.h"
#include "Renderer.h"
#include "Collider.h"
#include "PhysicsManager.h"
#include <iostream>

/// <summary>
/// Constructor for AirplanePlayer
/// </summary>
/// <param name="name">The name of the player</param>
AirplanePlayer::AirplanePlayer(std::string name) : AbstractGameObject(name), CollisionListener() {}

/// <summary>
/// Initialize the AirplanePlayer
/// </summary>
void AirplanePlayer::initialize() {
    std::cout << "AirplanePlayer initialized" << std::endl;

    // Set the initial position of the player
    this->transformable.setPosition(Game::WINDOW_WIDTH / 4, Game::WINDOW_HEIGHT - 30);

    // Attach input controller component
    PlayerInputController* inputController = new PlayerInputController("MyPlayerInput");
    this->attachComponent(inputController);

    // Attach movement component
    PlayerMovement* movement = new PlayerMovement("MyMovement");
    this->attachComponent(movement);

    // Attach renderer component
    Renderer* renderer = Renderer::createSprite("PlayerSprite", "eagle");
    attachComponent(renderer);

    // Retrieve the sprite and set up the collider
    sf::Sprite* sprite = renderer->getSprite();
    if (sprite != nullptr) {
        std::cout << "Position: " << sprite->getPosition().x << ":" << sprite->getPosition().y << std::endl;
        this->collider = new Collider("PlayerCollider");
        this->collider->setLocalBounds(sprite->getGlobalBounds());
        std::cout << "BOUNDS: " << sprite->getGlobalBounds().left << ":" << sprite->getGlobalBounds().top << ":" << sprite->getGlobalBounds().width << ":" << sprite->getGlobalBounds().height << std::endl;
    }
    else {
        std::cerr << "Error: sprite is nullptr" << std::endl;
    }

    // Set the collision listener and attach the collider component
    this->collider->setCollisionListener(this);
    this->attachComponent(this->collider);

    // Track the collider with the PhysicsManager
    PhysicsManager* physicsManager = PhysicsManager::getInstance();
    if (physicsManager != nullptr) {
        physicsManager->trackObject(this->collider);
    }
    else {
        std::cerr << "Error: PhysicsManager instance is not initialized." << std::endl;
    }
}

/// <summary>
/// Process input events
/// </summary>
/// <param name="event">The input event</param>
void AirplanePlayer::processInputs(sf::Event event) {
    AbstractGameObject::processInputs(event);
}

/// <summary>
/// Update the AirplanePlayer
/// </summary>
/// <param name="deltaTime">The time elapsed since the last update</param>
void AirplanePlayer::update(sf::Time deltaTime) {
    AbstractGameObject::update(deltaTime);
}

/// <summary>
/// Handle collision enter events
/// </summary>
/// <param name="contact">The game object that the player collided with</param>
void AirplanePlayer::onCollisionEnter(AbstractGameObject* contact) {
    // Handle collision enter if needed
}

/// <summary>
/// Handle collision exit events
/// </summary>
/// <param name="gameObject">The game object that the player stopped colliding with</param>
void AirplanePlayer::onCollisionExit(AbstractGameObject* gameObject) {
    // Handle collision exit if needed
}

