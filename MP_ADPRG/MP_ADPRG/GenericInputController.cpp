#include "GenericInputController.h"

GenericInputController::GenericInputController(std::string name) : AbstractComponent(name, Input) {
	this->type = Input;
}

GenericInputController::~GenericInputController() { 
	AbstractComponent::~AbstractComponent();
}

void GenericInputController::assignEvent(sf::Event event) {
	this->event = event;
}

void GenericInputController::perform() {

}