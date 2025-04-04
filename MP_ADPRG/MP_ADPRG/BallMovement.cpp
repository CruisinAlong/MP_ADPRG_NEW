// BallMovement.cpp
#include "BallMovement.h"
#include "BallObject.h"
#include <iostream>

BallMovement::BallMovement(std::string name) : AbstractComponent(name, AbstractComponent::Script) {
}

void BallMovement::perform() {
    BallObject* ball = dynamic_cast<BallObject*>(this->getOwner());
    if (ball && ball->isMoving) {
        sf::Vector2f position = ball->getPosition();
        position.x += 1.0f; // Move the ball to the right
        ball->setPosition(position.x, position.y);
    }
}
