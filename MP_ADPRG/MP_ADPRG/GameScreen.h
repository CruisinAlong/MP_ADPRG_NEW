#pragma once
#include "AbstractScene.h"
#include "AirplanePlayer.h"
#include "AirplaneSupport.h"
#include "EnemySwarmHandler.h"
#include "GameObjectPool.h"
#include "HUD.h"
#include "UIButton.h"
#include "UIText.h"
#include "GameObjectManager.h"
#include "ObjectPoolHolder.h"
#include "ProjectileObject.h"
#include "SceneManager.h"
#include "BGObject.h"
#include <iostream>
#include "EmptyGameObject.h"
#include "EnemyGroundSwarmHandler.h"
#include "UIData.h"
#include "BGMovement.h"
#include <ctime>

class GameScreen : public AbstractGameObject, public ButtonListener {
public:
    GameScreen(std::string name);
    void initialize() override;
    void onButtonClick(UIButton* button) override;
    void onButtonReleased(UIButton* button) override;
    void update(sf::Time deltaTime);

private:
    void endLevel();
    void startNextLevel();

    AirplanePlayer* planeObject;
    AirplaneSupport* support1;
    AirplaneSupport* support2;
    GameObjectPool* enemyPool;
    UIText* scoreText;
    UIData* scoreData;
    HUD* hud;
    UIButton* quitButton;
    UIText* quitButtonText;
    UIText* confirmationText;
    UIButton* yesButton;
    UIButton* noButton;
    UIText* yesButtonText;
    UIText* noButtonText;
    BGObject* bgObject;
    bool showConfirmationPopup;
    bool endLevelLoaded;
    sf::Time endLevelTimer; 
    const sf::Time endLevelDelay = sf::seconds(5);


};

