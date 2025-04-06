// MonkeyLevelScreen.cpp
#include "MonkeyLevelScreen.h"
#include "TextureManager.h"
#include "FastJumpingEnemySwarmHandler.h"
#include "SlowForwardEnemySwarmHandler.h"
#include "GameObjectManager.h"
#include "BGMovement.h"
#include "SoundManager.h"
#include <iostream>

// Constructor for MonkeyLevelScreen
MonkeyLevelScreen::MonkeyLevelScreen(std::string name) : AbstractGameObject(name), bgObject(nullptr), hud(nullptr), scoreText(nullptr) {}

// Initialize the MonkeyLevelScreen
void MonkeyLevelScreen::initialize() {
    std::cout << "MonkeyLevelScreen initialize called for: " << this->getName() << std::endl;

    // Create and add background object
    bgObject = new BGObject("bgObject");
    GameObjectManager::getInstance()->addObject(bgObject);

    // Create and add player object
    std::cout << "Creating PlaneObject" << std::endl;
    AirplanePlayer* planeObject = new AirplanePlayer("PlaneObject");
    std::cout << "Creating PhysicsManager" << std::endl;
    PhysicsManager::initialize("PhysicsManager", this);
    GameObjectManager::getInstance()->addObject(planeObject);

    // Create and add ground enemies manager
    srand(time(nullptr));
    std::cout << "Creating EnemiesManager" << std::endl;
    EmptyGameObject* enemiesGroundManager = new EmptyGameObject("EnemiesManager");
    SlowForwardEnemySwarmHandler* slowForwardHandler = new SlowForwardEnemySwarmHandler(5, "SlowForwardHandler", enemiesGroundManager);
    enemiesGroundManager->attachComponent(slowForwardHandler);
    GameObjectManager::getInstance()->addObject(enemiesGroundManager);

    // Create and add fast jumping enemies manager
    srand(time(nullptr));
    std::cout << "Creating EnemiesManager" << std::endl;
    EmptyGameObject* enemiesManager = new EmptyGameObject("EnemiesManager");
    FastJumpingEnemySwarmHandler* fastJumpingHandler = new FastJumpingEnemySwarmHandler(5, "FastJumpingHandler", enemiesManager);
    enemiesManager->attachComponent(fastJumpingHandler);
    GameObjectManager::getInstance()->addObject(enemiesManager);

    // Create and add HUD
    std::cout << "Creating HUD" << std::endl;
    hud = new HUD("HUD");
    GameObjectManager::getInstance()->addObject(hud);

    // Create and add score text
    scoreText = new UIText("scoreText");
    GameObjectManager::getInstance()->addObject(scoreText);
    scoreText->setPosition(50.0f, 10.0f);
    scoreText->setSize(20);
    scoreText->setText("SCORE: 1000000");

    // Initialize score data
    UIData* scoreData = UIManager::getInstance()->storeData(UIManager::SCORE_UI_KEY);
    scoreData->bindUIText(scoreText);
    scoreData->putInt(UIManager::SCORE_UI_KEY, 0);
    scoreData->refreshTextFromData("scoreText", UIManager::SCORE_UI_KEY, "Score: ");

    std::cout << "MonkeyLevelScreen initialization complete" << std::endl;

    // Play background music
    SoundManager::getInstance()->playMusic("Stage3");
}

// Update the MonkeyLevelScreen
void MonkeyLevelScreen::update(sf::Time deltaTime) {
    AbstractGameObject::update(deltaTime);

    // Update timers
    scoreIncrementTimer += deltaTime;
    if (isCooldownActive) {
        cooldownTimer += deltaTime;
        if (cooldownTimer >= cooldownDuration) {
            isCooldownActive = false;
            cooldownTimer = sf::Time::Zero;
        }
    }

    // Increment score if not in cooldown
    if (!isCooldownActive && scoreIncrementTimer >= scoreIncrementInterval) {
        UIData* scoreData = UIManager::getInstance()->getUIData(UIManager::SCORE_UI_KEY);
        int currentScore = scoreData->getInt(UIManager::SCORE_UI_KEY, 0);
        scoreData->putInt(UIManager::SCORE_UI_KEY, currentScore + 200); // Increment score by 200
        scoreData->refreshTextFromData("scoreText", UIManager::SCORE_UI_KEY, "Score: ");
        scoreIncrementTimer = sf::Time::Zero; // Reset the score increment timer
    }

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

// End the level
void MonkeyLevelScreen::endLevel() {
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

// Start the next level
void MonkeyLevelScreen::startNextLevel() {
    std::cout << "Starting next level." << std::endl;
    // Load the next level
    SceneManager::getInstance()->loadScene("TitleScene"); // Replace with the actual next level scene name
}

// Activate cooldown
void MonkeyLevelScreen::activateCooldown() {
    isCooldownActive = true;
    cooldownTimer = sf::Time::Zero;
}

// Reset cooldown timer
void MonkeyLevelScreen::resetCooldownTimer() {
    cooldownTimer = sf::Time::Zero;
}


