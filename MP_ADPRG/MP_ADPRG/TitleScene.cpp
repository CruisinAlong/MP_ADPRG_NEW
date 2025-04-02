// TitleScene.cpp
#include "TitleScene.h"
#include "TitleScreen.h"
#include "SceneManager.h"
#include <iostream>

TitleScene::TitleScene() : AbstractScene("TitleScene") {
    std::cout << "TitleScene created." << std::endl;
}

void TitleScene::onLoadResources() {
    std::cout << "TitleScene loading resources." << std::endl;
}

void TitleScene::onLoadObjects() {
    std::cout << "TitleScene loading objects." << std::endl;
    TitleScreen* titleScreen = new TitleScreen("TitleScreen");
    this->registerObject(titleScreen);
}

void TitleScene::onUnloadResources() {
    std::cout << "TitleScene unloading resources." << std::endl;
}

void TitleScene::onUnloadObjects() {
    std::cout << "TitleScene unloading objects." << std::endl;
    GameObjectManager::getInstance()->deleteAllObjectsInScene(); 
}
