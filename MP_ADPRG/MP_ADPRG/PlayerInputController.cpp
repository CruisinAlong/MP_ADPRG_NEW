#include "PlayerInputController.h"
#include <iostream>

PlayerInputController::PlayerInputController(std::string name) : GenericInputController(name) {

}

PlayerInputController::~PlayerInputController() {
    GenericInputController::~GenericInputController();

}

void PlayerInputController::perform() {

    bool keyFlag = false;
    if (event.type == sf::Event::KeyPressed) {
        keyFlag = true;
    }
    else if (event.type == sf::Event::KeyReleased) {
        keyFlag = false;
    }

    switch (event.key.code) {
        case sf::Keyboard::W:
            this->moveUp = keyFlag;
            break;
        case sf::Keyboard::A:
            this->moveLeft = keyFlag;
            break;
        case sf::Keyboard::S:
            this->moveDown = keyFlag;
            break;
        case sf::Keyboard::D:
            this->moveRight = keyFlag;
            break;
        case sf::Keyboard::Space:
            this->jump = keyFlag; 
            break;
    }
}

bool PlayerInputController::isUp() {
    return this->moveUp;
}
bool PlayerInputController::isDown() {
    return this->moveDown;
}
bool PlayerInputController::isLeft() {
    return this->moveLeft;
}
bool PlayerInputController::isRight() {
    return this->moveRight;
}
bool PlayerInputController::isJump() {
	return this->jump;

}
