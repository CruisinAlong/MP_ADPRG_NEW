#pragma once
#include "AbstractGameObject.h"
#include "Game.h"
#include <iostream>

class BGObject : public AbstractGameObject
{
public:
    BGObject(std::string name);
    void initialize() override;
    void update(sf::Time deltaTime) override;
    void processInputs(sf::Event event) override; 
private:
    const float SPEED_MULTIPLIER = 100.f;
};
