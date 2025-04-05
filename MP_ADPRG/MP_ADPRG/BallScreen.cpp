// BallScreen.cpp
#include "BallScreen.h"
#include "TextureManager.h"
#include "GameObjectManager.h"
#include "UIManager.h"
#include "BGObject.h"
#include "AirplanePlayer.h"
#include "BallObjectHandler.h"
#include <iostream>

BallScreen::BallScreen(std::string name) : AbstractGameObject(name), ButtonListener() {}

void BallScreen::initialize() {
    std::cout << "BallScreen initialize called for: " << this->getName() << std::endl;

    if (PhysicsManager::getInstance() == nullptr) {
        std::cout << "Creating PhysicsManager" << std::endl;
        PhysicsManager::initialize("PhysicsManager", this);
    }

    // Load background
    std::cout << "Creating BGObject" << std::endl;
    bgObject = new BGObject("bgObject");
    GameObjectManager::getInstance()->addObject(bgObject);
    std::cout << "BGObject created and added to GameObjectManager" << std::endl;

    // Load player
    std::cout << "Creating PlayerObject" << std::endl;
    player = new AirplanePlayer("PlayerObject");
    GameObjectManager::getInstance()->addObject(player);
    std::cout << "PlayerObject created and added to GameObjectManager" << std::endl;

    // Initialize ball handler
    srand(time(nullptr));
    std::cout << "Creating BallManager" << std::endl;
    EmptyGameObject* ballManager = new EmptyGameObject("BallManager");
    BallObjectHandler* ballHandler = new BallObjectHandler(10, "BallHandler", ballManager);
    ballManager->attachComponent(ballHandler);
    GameObjectManager::getInstance()->addObject(ballManager);
    std::cout << "BallManager and BallHandler created and added to GameObjectManager" << std::endl;

    // Initialize score text and score data
    std::cout << "Creating scoreText" << std::endl;
    UIText* scoreText = new UIText("scoreText");
    GameObjectManager::getInstance()->addObject(scoreText);
    scoreText->setPosition(10.0f, 10.0f);
    scoreText->setSize(20);
    scoreText->setText("SCORE: 1000000");
    std::cout << "scoreText created and added to GameObjectManager" << std::endl;

    std::cout << "Creating scoreData" << std::endl;
    UIData* scoreData = UIManager::getInstance()->storeData(UIManager::SCORE_UI_KEY);
    scoreData->bindUIText(scoreText);
    scoreData->putInt(UIManager::SCORE_UI_KEY, 0);
    scoreData->refreshTextFromData("scoreText", UIManager::SCORE_UI_KEY, "Score: ");
    std::cout << "scoreData created and bound to scoreText" << std::endl;
}


void BallScreen::onButtonClick(UIButton* button) {
    std::cout << button->getName() << " clicked" << std::endl;
    // Handle button click events if needed
}

void BallScreen::onButtonReleased(UIButton* button) {
    std::cout << button->getName() << " released" << std::endl;
    // Handle button release events if needed
}