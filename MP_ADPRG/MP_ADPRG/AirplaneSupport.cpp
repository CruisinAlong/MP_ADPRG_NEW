#include "AirplaneSupport.h"
#include "TextureManager.h"
#include <cmath>
#include <iostream>

const float SPEED = 100.f;
const float FREQUENCY = 2.0f;

AirplaneSupport::AirplaneSupport(std::string name) : AbstractGameObject(name){
}

void AirplaneSupport::initialize() {
    this->sprite = new sf::Sprite();
    sf::Texture* texture = TextureManager::getInstance()->getTexture("raptor");
    this->sprite->setTexture(*texture);
    sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
    this->sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
    this->sprite->setPosition(0, 0);

    Renderer* renderer = new Renderer("PlayerSupport");
    renderer->assignDrawable(sprite);
    this->attachComponent(renderer);

    AirplaneSupportMovement* logicComponent1 = new AirplaneSupportMovement("AirplaneSupportMovement_1");
    this->attachComponent(logicComponent1);

    AirplaneSupportMovement* logicComponent2 = new AirplaneSupportMovement("AirplaneSupportMovement_2");
    this->attachComponent(logicComponent2);

}

void AirplaneSupport::processInputs(sf::Event event) {
}

void AirplaneSupport::update(sf::Time deltaTime) {
    AbstractGameObject::update(deltaTime);
}
