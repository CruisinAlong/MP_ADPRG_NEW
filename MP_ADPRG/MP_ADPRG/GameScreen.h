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
#include <ctime>

class GameScreen : public AbstractGameObject, public ButtonListener {
public:
    GameScreen(std::string name);
    void initialize() override;
    void onButtonClick(UIButton* button) override;
    void onButtonReleased(UIButton* button) override;

private:
    AirplanePlayer* planeObject;
    AirplaneSupport* support1;
    AirplaneSupport* support2;
    GameObjectPool* enemyPool;
    HUD* hud;
    UIButton* quitButton;
    UIText* quitButtonText;
    UIText* confirmationText;
    UIButton* yesButton;
    UIButton* noButton;
    UIText* yesButtonText;
    UIText* noButtonText;
    bool showConfirmationPopup;
};

