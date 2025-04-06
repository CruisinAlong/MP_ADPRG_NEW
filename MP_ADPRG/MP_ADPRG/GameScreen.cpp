// GameScreen.cpp
#include "GameScreen.h"
#include "TextureManager.h"
#include "GameObjectManager.h"
#include "AbstractGameObject.h"
#include "ResultsScreen.h"
#include "SoundManager.h"
#include <iostream>
#include <string>

GameScreen::GameScreen(std::string name) : AbstractGameObject(name), ButtonListener(), showConfirmationPopup(false), endLevelLoaded(false) {}
/// <summary>
/// First level
/// </summary>
void GameScreen::initialize() {
    std::cout << "GameScreen initialize called for: " << this->getName() << std::endl;

    sf::Texture* btnNormalTexture = TextureManager::getInstance()->getTexture("btn_normal");
    sf::Texture* btnPressedTexture = TextureManager::getInstance()->getTexture("btn_pressed");

    bgObject = new BGObject("bgObject");
    GameObjectManager::getInstance()->addObject(bgObject);

    std::cout << "Creating PlaneObject" << std::endl;
    AirplanePlayer* planeObject = new AirplanePlayer("PlaneObject");
    if (PhysicsManager::getInstance() == nullptr) {
        PhysicsManager::initialize("PhysicsManager", planeObject);
    }
    GameObjectManager::getInstance()->addObject(planeObject);



    srand(time(nullptr));
    std::cout << "Creating EnemiesManager" << std::endl;
    EmptyGameObject* enemiesManager = new EmptyGameObject("EnemiesManager");
    EnemySwarmHandler* swarmHandler = new EnemySwarmHandler(5, "SwarmHandler", enemiesManager);
    enemiesManager->attachComponent(swarmHandler);
    GameObjectManager::getInstance()->addObject(enemiesManager);

    srand(time(nullptr));
    std::cout << "Creating EnemiesManager" << std::endl;
    EmptyGameObject* enemiesGroundManager = new EmptyGameObject("EnemiesManager");
    EnemyGroundSwarmHandler* swarmGroundHandler = new EnemyGroundSwarmHandler(5, "GroundSwarmHandler", enemiesGroundManager);
    enemiesGroundManager->attachComponent(swarmGroundHandler);
    GameObjectManager::getInstance()->addObject(enemiesGroundManager);

    std::cout << "Creating HUD" << std::endl;
    hud = new HUD("HUD");
    GameObjectManager::getInstance()->addObject(hud);

    std::cout << "Creating ConfirmationText" << std::endl;
    confirmationText = new UIText("ConfirmationText");
    confirmationText->setText("Are you sure you want to go back to the menu?");
    confirmationText->setPosition(320.0f, 200.0f);
    confirmationText->setEnabled(false);
    GameObjectManager::getInstance()->addObject(confirmationText);

    std::cout << "Creating YesButton" << std::endl;
    yesButton = new UIButton("YesButton", btnNormalTexture, btnPressedTexture);
    yesButton->setButtonListener(this);
    yesButton->setPosition(270.0f, 250.0f);
    yesButton->setEnabled(false);
    GameObjectManager::getInstance()->addObject(yesButton);

    std::cout << "Creating NoButton" << std::endl;
    noButton = new UIButton("NoButton", btnNormalTexture, btnPressedTexture);
    noButton->setButtonListener(this);
    noButton->setPosition(370.0f, 250.0f);
    noButton->setEnabled(false);
    GameObjectManager::getInstance()->addObject(noButton);

    std::cout << "Creating YesButtonText" << std::endl;
    yesButtonText = new UIText("YesButtonText");
    yesButtonText->setText("Yes");
    yesButtonText->setPosition(yesButton->getTransformable()->getPosition().x, yesButton->getTransformable()->getPosition().y);
    yesButtonText->setEnabled(false);
    GameObjectManager::getInstance()->addObject(yesButtonText);

    std::cout << "Creating NoButtonText" << std::endl;
    noButtonText = new UIText("NoButtonText");
    noButtonText->setText("No");
    noButtonText->setPosition(noButton->getTransformable()->getPosition().x, noButton->getTransformable()->getPosition().y);
    noButtonText->setEnabled(false);
    GameObjectManager::getInstance()->addObject(noButtonText);

    MainMenuScreen* mainMenu = new MainMenuScreen("MainMenu");
    GameObjectManager::getInstance()->addObject(mainMenu);
    mainMenu->setEnabled(false);

    scoreText = new UIText("scoreText");
    GameObjectManager::getInstance()->addObject(scoreText);
    scoreText->setPosition(50.0f, 10.0f);
    scoreText->setSize(20);
    scoreText->setText("SCORE: 1000000");

    UIData* scoreData = UIManager::getInstance()->storeData(UIManager::SCORE_UI_KEY);
    scoreData->bindUIText(scoreText);
    scoreData->putInt(UIManager::SCORE_UI_KEY, 0);
    scoreData->refreshTextFromData("scoreText", UIManager::SCORE_UI_KEY, "Score: ");

    SoundManager::getInstance()->playMusic("Stage1");


    std::cout << "GameScreen initialization complete" << std::endl;
}

void GameScreen::onButtonClick(UIButton* button) {
    std::cout << button->getName() << " clicked" << std::endl;
    if (button->getName() == "QuitButton") {
        showConfirmationPopup = true;
        confirmationText->setEnabled(true);
        yesButton->setEnabled(true);
        noButton->setEnabled(true);
        yesButtonText->setEnabled(true);
        noButtonText->setEnabled(true);
    }
    else if (button->getName() == "YesButton") {
        SceneManager::getInstance()->loadScene("MainMenuScene");
    }
    else if (button->getName() == "NoButton") {
        showConfirmationPopup = false;
        confirmationText->setEnabled(false);
        yesButton->setEnabled(false);
        noButton->setEnabled(false);
        yesButtonText->setEnabled(false);
        noButtonText->setEnabled(false);
    }
}

void GameScreen::onButtonReleased(UIButton* button) {
    std::cout << button->getName() << " released" << std::endl;
}

void GameScreen::update(sf::Time deltaTime) {
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

void GameScreen::endLevel() {
    std::cout << "Level ended." << std::endl;

    // Initialize end level text
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


void GameScreen::startNextLevel() {
    std::cout << "Starting next level." << std::endl;
    // Load the next level
    SceneManager::getInstance()->loadScene("BallScene");
	ApplicationManager::getInstance()->resumeApplication();
}

