// BallScreen.h
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

class BallScreen : public AbstractGameObject, public ButtonListener {
public:
    BallScreen(std::string name);
    void initialize() override;
    void update(sf::Time deltaTime) override;
    void onButtonClick(UIButton* button) override;
    void onButtonReleased(UIButton* button) override;

private:
    void endLevel();
    void startNextLevel();

    BGObject* bgObject;
    UIText* scoreText;
    sf::Time endLevelTimer; // Timer for end level delay
    const sf::Time endLevelDelay = sf::seconds(5); // Delay duration
    bool endLevelLoaded = false;
    AirplanePlayer* player;
    UIData* scoreData;
};
