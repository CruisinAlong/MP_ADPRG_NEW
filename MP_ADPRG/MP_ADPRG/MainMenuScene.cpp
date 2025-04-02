// MainMenuScene.cpp
#include "MainMenuScene.h"
#include "MainMenuScreen.h"
#include "GameObjectManager.h"
#include <iostream>

MainMenuScene::MainMenuScene() : AbstractScene("MainMenuScene") {
    std::cout << "MainMenuScene created." << std::endl;
}

void MainMenuScene::onLoadResources() {
    // Load any resources needed for the main menu here
    std::cout << "MainMenuScene loading resources." << std::endl;
}

void MainMenuScene::onLoadObjects() {
    std::cout << "MainMenuScene loading objects." << std::endl;
    MainMenuScreen* menuScreen = new MainMenuScreen("MainMenuScreen");
    this->registerObject(menuScreen);
}

void MainMenuScene::onUnloadResources() {
    // Unload any resources loaded for the main menu here
    std::cout << "MainMenuScene unloading resources." << std::endl;
}

void MainMenuScene::onUnloadObjects() {
    // Unload any objects created for the main menu here
    std::cout << "MainMenuScene unloading objects." << std::endl;

}
