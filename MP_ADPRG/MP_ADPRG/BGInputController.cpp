#include "BGInputController.h"
#include <iostream>

BGInputController::BGInputController(std::string name) : GenericInputController(name) {
    std::cout << "BGInputController [" << name << "] created." << std::endl; // Debug log
}

BGInputController::~BGInputController() {
    std::cout << "BGInputController [" << name << "] destroyed." << std::endl; // Debug log
}
/// <summary>
/// Sets off the flags to move the background, player is actually not moving to show an effect of a moving camera
/// </summary>
void BGInputController::perform() {
    bool keyFlag = false;
    if (event.type == sf::Event::KeyPressed) {
        keyFlag = true;

    }
    else if (event.type == sf::Event::KeyReleased) {
        keyFlag = false;

    }

    switch (event.key.code) {
    case sf::Keyboard::D:
        this->move = keyFlag;
        break;
    default:
        break;
    }
}

bool BGInputController::isMove() {
    return this->move;
}


