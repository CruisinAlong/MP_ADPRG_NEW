#pragma once
#include "AbstractComponent.h"
#include <SFML/Window/Event.hpp>

class GenericInputController : public AbstractComponent {
public:
    GenericInputController(std::string name);
    ~GenericInputController();

    void perform() override;
    void assignEvent(sf::Event event);
protected:
    sf::Event event;
};
