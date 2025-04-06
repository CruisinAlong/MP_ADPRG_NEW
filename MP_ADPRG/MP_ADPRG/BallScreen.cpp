// BallScreen.cpp
#include "BallScreen.h"
#include "TextureManager.h"
#include "GameObjectManager.h"
#include "UIManager.h"
#include "BGObject.h"
#include "AirplanePlayer.h"
#include "BallObjectHandler.h"
#include "BallPlayer.h"
#include <iostream>

BallScreen::BallScreen(std::string name) : AbstractGameObject(name), ButtonListener() {}

void BallScreen::initialize() {
    std::cout << "BallScreen initialize called for: " << this->getName() << std::endl;

    // Load background
    std::cout << "Creating BGObject" << std::endl;
    bgObject = new BGObject("bgObject");
    GameObjectManager::getInstance()->addObject(bgObject);
    std::cout << "BGObject created and added to GameObjectManager" << std::endl;

    // Load player
    std::cout << "Creating PlayerObject" << std::endl;
    BallPlayer* player = new BallPlayer("PlayerObject"); 
    EmptyGameObject* physicsParent = new EmptyGameObject("PhysicsParent");
        std::cout << "Creating PhysicsManager" << std::endl;
        PhysicsManager::initialize("PhysicsManager", this);
    
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
    scoreText = new UIText("scoreText");
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

    SoundManager::getInstance()->playMusic("Stage2");
}


void BallScreen::onButtonClick(UIButton* button) {
    std::cout << button->getName() << " clicked" << std::endl;
    // Handle button click events if needed
}

void BallScreen::onButtonReleased(UIButton* button) {
    std::cout << button->getName() << " released" << std::endl;
    // Handle button release events if needed
}

/// <summary>
/// Determines the start of a new level after reaching a certain distance.
/// </summary>
/// <param name="deltaTime"></param>
void BallScreen::update(sf::Time deltaTime) {
    AbstractGameObject::update(deltaTime);

    // Check if the level should end
    BGMovement* bgMovement = dynamic_cast<BGMovement*>(bgObject->getComponentByName("BGMovement"));
    if (bgMovement && bgMovement->isLevelFinished()) {
        endLevel();
    }
    // Update the end level timer
    if (endLevelLoaded) {
        endLevelTimer += deltaTime;
        if (endLevelTimer >= endLevelDelay) {
            startNextLevel();
            endLevelLoaded = false; // Reset the flag
            endLevelTimer = sf::Time::Zero; // Reset the timer
        }
    }
}
/// <summary>
/// Ends the level and shows the score.
/// </summary>
void BallScreen::endLevel() {
    std::cout << "Level ended." << std::endl;

    // Display end level text
    UIText* endLevelText = new UIText("EndLevelText");
    GameObjectManager::getInstance()->addObject(endLevelText);
    endLevelText->setText("Level Complete!");
    endLevelText->setPosition(320.0f, 240.0f); // Center of the screen

    if (scoreText) {
        scoreText->setPosition(320.0f, 280.0f); // Position it right below endLevelText
        scoreText->setSize(30); // Resize the text
    }

    // Set the flag to indicate end level objects are loaded
    endLevelLoaded = true;
}
/// <summary>
/// Loads the next scene.
/// </summary>
void BallScreen::startNextLevel() {
    std::cout << "Starting next level." << std::endl;
    // Load the next level
    SceneManager::getInstance()->loadScene("MonkeyLevelScene");
}