// MonkeyLevelScene.cpp
#include "MonkeyLevelScene.h"
#include "GameObjectManager.h"
#include <iostream>

MonkeyLevelScene::MonkeyLevelScene() : AbstractScene("MonkeyLevelScene") {}

void MonkeyLevelScene::onLoadResources() {
    std::cout << "MonkeyLevelScene loading resources." << std::endl;
    // Load resources here if needed
}

void MonkeyLevelScene::onLoadObjects() {
    std::cout << "MonkeyLevelScene loading objects." << std::endl;
    MonkeyLevelScreen* monkeyLevelScreen = new MonkeyLevelScreen("MonkeyLevelScreen");
    this->registerObject(monkeyLevelScreen);
}

void MonkeyLevelScene::onUnloadObjects() {
    SoundManager::getInstance()->stopMusic();
    std::cout << "Unloading objects in scene: " << this->getSceneName() << std::endl;
    GameObjectManager::getInstance()->deleteAllObjectsInScene();
    std::cout << "Objects unloaded in scene: " << this->getSceneName() << std::endl;
}

void MonkeyLevelScene::onUnloadResources() {
	std::cout << "MonkeyLevelScene unloading resources." << std::endl;
	// Unload resources here if needed
}
