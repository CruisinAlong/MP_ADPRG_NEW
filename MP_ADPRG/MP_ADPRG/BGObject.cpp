#include "BGObject.h"
#include "BGMovement.h"
#include <iostream>
#include "TextureManager.h"

BGObject::BGObject(std::string name) : AbstractGameObject(name) {
}

void BGObject::initialize() {
    std::cout << "BGObject initialized" << std::endl;
    // Load the texture
    sf::Texture* texture = TextureManager::getInstance()->getTexture("desert_bg");
    sf::Vector2u textureSize = texture->getSize();

    // Calculate the number of sprites needed to cover the window width
    int numSprites = (Game::WINDOW_WIDTH / textureSize.x) + 5;

    // Create and position the sprites
    for (int i = 0; i < numSprites; ++i) {
        sf::Sprite* sprite = new sf::Sprite();
        sprite->setTexture(*texture);
        sprite->setTextureRect(sf::IntRect(0, 0, textureSize.x, Game::WINDOW_HEIGHT * 8));
        sprite->setPosition(i * textureSize.x, -Game::WINDOW_HEIGHT * 7);

        // Store the sprite in a vector for later use
        sprites.push_back(sprite);

        // Create a renderer for each sprite and attach it
        Renderer* renderer = new Renderer("BGSprite" + std::to_string(i));
        renderer->assignDrawable(sprite);
        this->attachComponent(renderer);
    }
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
