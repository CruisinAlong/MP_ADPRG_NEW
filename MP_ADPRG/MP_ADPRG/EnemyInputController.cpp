#include "EnemyInputController.h"
#include <iostream>

EnemyInputController::EnemyInputController(std::string name) : GenericInputController(name), move(false) {
    std::cout << "EnemyInputController [" << name << "] created." << std::endl; // Debug log
}

void EnemyInputController::perform() {
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

bool EnemyInputController::isMove() {
    return this->move;
}



