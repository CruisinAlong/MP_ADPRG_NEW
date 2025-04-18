#include "EnemyBehavior.h"
#include "AbstractGameObject.h"
#include "Game.h"
#include <SFML/Graphics.hpp>

EnemyBehavior::EnemyBehavior(std::string name) : AbstractComponent(name, Script), movementType(Static), delay(0.0f), ticks(0.0f), jumpDelay(0.0f), hasJumped(false) {
    this->reset();
}
/// <summary>
/// Determines enemy movement, one is "static" where it moves along with the background, one moves them slowly forward and the last is a speedy advance.
/// </summary>
void EnemyBehavior::perform() {
    if (owner == nullptr) {
        std::cerr << "EnemyBehavior [" << name << "] error: owner not set." << std::endl;
        return;
    }

    sf::Transformable* transformable = owner->getTransformable();
    if (transformable == nullptr) {
        std::cerr << "EnemyBehavior [" << name << "] error: transformable not found." << std::endl;
        return;
    }

    ticks += deltaTime.asSeconds();

    switch (movementType) {
    case Static:
        if (inputController != nullptr) {
            inputController->perform();
        }
        else {
            std::cerr << "Error: inputController is nullptr." << std::endl;
        }

        if (ticks >= delay) {
            if (inputController->isMove()) {
                transformable->move(-SPEED_MULTIPLIER * deltaTime.asSeconds(), 0);
                sf::Vector2f position = transformable->getPosition();
            }
        }
        break;

    case SlowForward:
        if (ticks >= delay) {
            transformable->move(-SPEED_MULTIPLIER * deltaTime.asSeconds(), 0);
        }
        break;
    case NonMoving:
        // Do nothing, the enemy will stop moving
        break;
    case FastJump:
        if (ticks >= delay) {
            if (!hasJumped && ticks >= delay + jumpDelay) { 
                transformable->move(-500.0f * deltaTime.asSeconds(), -300.0f * deltaTime.asSeconds()); // Fast speed and jump
                hasJumped = true; // Jump once
            }
            else {
                transformable->move(-500.0f * deltaTime.asSeconds(), 0); // Continue moving fast horizontally
            }
        }
        break;
    }
}


void EnemyBehavior::configure(EnemyMovementType type, float delay) {
    this->movementType = type;
    this->delay = delay;
}

void EnemyBehavior::reset() {
    ticks = 0.0f;
}

void EnemyBehavior::setInputController(EnemyInputController* inputController) {
    this->inputController = inputController;
}



