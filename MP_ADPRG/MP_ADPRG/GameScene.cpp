// GameScene.cpp
#include "GameScene.h"
#include "GameScreen.h"
#include "SceneManager.h"
#include <iostream>

GameScene::GameScene() : AbstractScene("GameScene") {
    std::cout << "GameScene created." << std::endl;
}

void GameScene::onLoadResources() {
    std::cout << "GameScene loading resources." << std::endl;
}

void GameScene::onLoadObjects() {
    std::cout << "GameScene loading objects." << std::endl;
    GameScreen* gameScreen = new GameScreen("GameScreen");
    this->registerObject(gameScreen);

}

void GameScene::onUnloadResources() {
    std::cout << "GameScene unloading resources." << std::endl;
}

void GameScene::onUnloadObjects() {
    std::cout << "GameScene unloading objects." << std::endl;
    GameObjectManager::getInstance()->deleteAllObjectsInScene();
}
