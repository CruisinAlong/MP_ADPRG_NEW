#include "BGMovement.h"
#include "BGObject.h"
#include <iostream>

BGMovement::BGMovement(std::string name) : AbstractComponent(name, Script) {
}

BGMovement::~BGMovement() {
    // Clean up the BGInputController
    delete inputController;
}

void BGMovement::perform() {
    BGObject* bgObject = (BGObject*)this->getOwner();
    sf::Transformable* bgTransformable = bgObject->getTransformable();
    if (bgTransformable == nullptr) {
        std::cout << "bgTransformable not found" << std::endl;
        return;
    }

    inputController->perform();

    if (inputController->isMove()) {
        sf::Vector2f offset(-SPEED * this->deltaTime.asSeconds(), 0.0f);
        bgTransformable->move(offset);
        moving = true;

        // Debug log to see if the background is moving
        sf::Vector2f newPosition = bgTransformable->getPosition();
    }
    else {
        moving = false;
    }
}

void BGMovement::setInputController(BGInputController* inputController) {
    this->inputController = inputController;
}


