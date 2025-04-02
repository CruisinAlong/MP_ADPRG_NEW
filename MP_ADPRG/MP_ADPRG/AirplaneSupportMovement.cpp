#include "AirplaneSupportMovement.h"
#include "AbstractGameObject.h"
#include <iostream>

AirplaneSupportMovement::AirplaneSupportMovement(std::string name) : AbstractComponent(name, ComponentType::Script) {
    if (name == "AirplaneSupportMovement_1") {
        direction = 1.0f; // Move left to right
    }
    else if (name == "AirplaneSupportMovement_2") {
        direction = -1.0f; // Move right to left
    }
    std::cout << "AirplaneSupportMovement [" << name << "] initialized with directionLR: " << direction << ", directionRL: " << direction << std::endl;
}

void AirplaneSupportMovement::perform() {

    if (name == "AirSupport_1") {
        elapsedTime += deltaTime.asSeconds();
        if (elapsedTime >= 3.0f) {
            direction *= -1;
            elapsedTime = 0.f;
            std::cout << "1: Reversed Direction " << direction << std::endl;
        }

    }
    else if (name == "AirSupport_2") {
        elapsedTime += deltaTime.asSeconds();
        if (elapsedTime >= 3.0f) {
            direction *= -1;
            elapsedTime = 0.f;
            std::cout << "2: Reversed Direction " << direction << std::endl;
        }
    }
    float deltaSeconds = deltaTime.asSeconds();
    float movement = SPEED * deltaSeconds * direction;
    // Move the airplane side to side
}



