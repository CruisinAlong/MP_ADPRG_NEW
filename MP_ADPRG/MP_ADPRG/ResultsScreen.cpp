// ResultsScreen.cpp
#include "ResultsScreen.h"
#include "GameObjectManager.h"
#include <iostream>

ResultsScreen::ResultsScreen(std::string name) : AbstractGameObject(name) {}
/// <summary>
/// Shows the score of the player
/// </summary>
void ResultsScreen::initialize() {
    std::cout << "ResultsScreen initialized" << std::endl;



    // Initialize results background sprite using createSprite
    Renderer* renderer = Renderer::createSprite("BGSprite", "results_bg");
    attachComponent(renderer);
    sf::Sprite* sprite = renderer->getSprite();
    sprite->setPosition(320.0f, 200.0f); // Position it appropriately
    sprite->setScale(1.0f, 1.0f); 

    GameObjectManager::getInstance()->addObject(this);
}
