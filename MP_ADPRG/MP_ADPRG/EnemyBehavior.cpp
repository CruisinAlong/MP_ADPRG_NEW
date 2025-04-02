#include "EnemyBehavior.h"
#include "AbstractGameObject.h"
#include "Game.h"
#include <SFML/Graphics.hpp>

EnemyBehavior::EnemyBehavior(std::string name) : AbstractComponent(name, Script), movementType(Static), delay(0.0f), ticks(0.0f) {
    this->reset();
}

EnemyBehavior::~EnemyBehavior() {
    delete inputController;
}


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



