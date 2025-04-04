#include "BGMovement.h"
#include "BGObject.h"
#include <iostream>

BGMovement::BGMovement(std::string name) : AbstractComponent(name, Script) {    
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

        // Update distance traveled
        distanceTraveled += std::abs(offset.x);
		std::cout << "Distance traveled: " << distanceTraveled << std::endl;

        // Check if the level should end
        if (distanceTraveled >= LEVEL_END_DISTANCE) {
            levelFinished = true;
        }

        sf::Vector2f newPosition = bgTransformable->getPosition();

    }
    else {
        moving = false;
    }
}

void BGMovement::setInputController(BGInputController* inputController) {
    this->inputController = inputController;
}

bool BGMovement::isLevelFinished() const {
    return levelFinished;
}


