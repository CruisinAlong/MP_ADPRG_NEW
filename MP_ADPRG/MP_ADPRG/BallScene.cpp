// BallScene.cpp
#include "BallScene.h"
#include "BallScreen.h"
#include "GameObjectManager.h"
#include "SceneManager.h"
#include <iostream>

BallScene::BallScene() : AbstractScene("BallScene") {
    std::cout << "BallScene created." << std::endl;
}

void BallScene::onLoadResources() {
    std::cout << "BallScene loading resources." << std::endl;
    // Load resources here if needed
}

void BallScene::onLoadObjects() {
    std::cout << "BallScene loading objects." << std::endl;
    BallScreen* ballScreen = new BallScreen("BallScreen");
    this->registerObject(ballScreen);
}

void BallScene::onUnloadResources() {
    std::cout << "BallScene unloading resources." << std::endl;
    // Unload resources here if needed
}

void BallScene::onUnloadObjects() {
    std::cout << "BallScene unloading objects." << std::endl;
    GameObjectManager::getInstance()->deleteAllObjectsInScene();
}
