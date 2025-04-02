#pragma once
#include "AbstractGameObject.h"
#include "AirplaneSupportMovement.h"

class AirplaneSupport : public AbstractGameObject
{
public:
    AirplaneSupport(std::string name);
    void initialize() override;
    void update(sf::Time deltaTime) override;
    void processInputs(sf::Event event) override;
private:
    const float SPEED = 100.f;

};
