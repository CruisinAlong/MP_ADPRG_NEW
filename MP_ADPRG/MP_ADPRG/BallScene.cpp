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
/// <summary>
/// Stops music and detaches the PhysicsManager from the current scene.
/// </summary>
void BallScene::onUnloadObjects() {
    std::cout << "BallScene unloading objects." << std::endl;
    SoundManager::getInstance()->stopMusic(); 
    EmptyGameObject* emptyParent = new EmptyGameObject("EmptyParent");
    GameObjectManager::getInstance()->addObject(emptyParent);

    // Rebind the PhysicsManager to the new EmptyGameObject
    PhysicsManager::getInstance()->rebindParent(emptyParent);
    GameObjectManager::getInstance()->deleteAllObjectsInScene();
}
