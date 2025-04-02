#include "BGObject.h"
#include "BGMovement.h"
#include <iostream>
#include "TextureManager.h"

BGObject::BGObject(std::string name) : AbstractGameObject(name) {
}

void BGObject::initialize() {
    std::cout << "BGObject initialized" << std::endl;
    sprite = new sf::Sprite();
    sprite->setTexture(*TextureManager::getInstance()->getTexture("desert_bg"));
    sf::Vector2u textureSize = sprite->getTexture()->getSize();
    sprite->setTextureRect(sf::IntRect(0, 0, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT * 8));
    sprite->setPosition(0, -Game::WINDOW_HEIGHT * 7);

    Renderer* renderer = new Renderer("BGSprite");
    renderer->assignDrawable(sprite);
    this->attachComponent(renderer);
    BGInputController* inputController = new BGInputController("BGInputController");
    this->attachComponent(inputController);
    BGMovement* movement = new BGMovement("BGMovement");
    this->attachComponent(movement);


    movement->setInputController(inputController);
}

void BGObject::processInputs(sf::Event event) {
    AbstractGameObject::processInputs(event); 
}

void BGObject::update(sf::Time deltaTime) {
    // Call the base class update to update child objects
    AbstractGameObject::update(deltaTime);
}
