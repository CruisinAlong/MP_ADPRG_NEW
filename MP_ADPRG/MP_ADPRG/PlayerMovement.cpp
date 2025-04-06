#include "PlayerMovement.h"
#include "AirplanePlayer.h"
#include "PlayerInputController.h"
#include "ObjectPoolHolder.h"
#include "ProjectileObject.h"

#include <iostream>

PlayerMovement::PlayerMovement(std::string name) : AbstractComponent(name, Script), projectilePool(nullptr), isJumping(false), jumpSpeed(300.0f), gravity(500.0f), velocityY(0.0f), playerHeight(30.0f) { 
    std::cout << "PlayerMovement [" << name << "] created." << std::endl;
}

void PlayerMovement::perform() {
    AirplanePlayer* airplanePlayer = (AirplanePlayer*)this->getOwner();
    PlayerInputController* inputController = (PlayerInputController*)(airplanePlayer->getComponentsOfType(ComponentType::Input)[0]);
    sf::Transformable* playerTransformable = airplanePlayer->getTransformable();
    if (playerTransformable == nullptr || inputController == nullptr) {
        std::cout << "PlayerMovement [" << name << "] error: playerTransformable or inputController not found." << std::endl;
        return;
    }

    sf::Vector2f offset(0.0f, 0.0f);


    if (inputController->isJump() && !isJumping) {
        isJumping = true;
        velocityY = -jumpSpeed;
    }

    if (isJumping) {
        velocityY += gravity * this->deltaTime.asSeconds();
        playerTransformable->move(0, velocityY * this->deltaTime.asSeconds());

        if (playerTransformable->getPosition().y >= Game::WINDOW_HEIGHT - playerHeight) { 
            playerTransformable->setPosition(playerTransformable->getPosition().x, Game::WINDOW_HEIGHT - playerHeight);
            isJumping = false;
            velocityY = 0.0f;
        }
    }
}
