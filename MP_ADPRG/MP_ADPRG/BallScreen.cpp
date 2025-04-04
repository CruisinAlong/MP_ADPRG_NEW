// BallScreen.cpp
#include "BallScreen.h"
#include "TextureManager.h"
#include "GameObjectManager.h"
#include "BGObject.h"
#include "AirplanePlayer.h"
#include "BallObjectHandler.h"
#include <iostream>

BallScreen::BallScreen(std::string name) : AbstractGameObject(name), ButtonListener() {}

void BallScreen::initialize() {
    std::cout << "BallScreen initialize called for: " << this->getName() << std::endl;

    // Load background
    bgObject = new BGObject("bgObject");
    GameObjectManager::getInstance()->addObject(bgObject);

    // Load player
    std::cout << "Creating PlayerObject" << std::endl;
    player = new AirplanePlayer("PlayerObject");
    GameObjectManager::getInstance()->addObject(player);

    // Initialize ball handler
    srand(time(nullptr));
    std::cout << "Creating BallManager" << std::endl;
    EmptyGameObject* ballManager = new EmptyGameObject("BallManager");
    BallObjectHandler* ballHandler = new BallObjectHandler(10, "BallHandler", ballManager);
    ballManager->attachComponent(ballHandler);
    GameObjectManager::getInstance()->addObject(ballManager);
}

void BallScreen::onButtonClick(UIButton* button) {
    std::cout << button->getName() << " clicked" << std::endl;
    // Handle button click events if needed
}

void BallScreen::onButtonReleased(UIButton* button) {
    std::cout << button->getName() << " released" << std::endl;
    // Handle button release events if needed
}