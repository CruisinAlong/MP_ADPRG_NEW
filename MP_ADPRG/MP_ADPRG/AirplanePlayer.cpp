#include "AirplanePlayer.h"



AirplanePlayer::AirplanePlayer(std::string name) : AbstractGameObject(name), CollisionListener()
{
}


void AirplanePlayer::initialize()
{
	std::cout << "AirplanePlayer initialized" << std::endl;

	this->transformable.setPosition(Game::WINDOW_WIDTH / 4, Game::WINDOW_HEIGHT - 50);

	PlayerInputController* inputController = new PlayerInputController("MyPlayerInput");
	this->attachComponent(inputController);

	PlayerMovement* movement = new PlayerMovement("MyMovement");
	this->attachComponent(movement);

	Renderer* renderer = Renderer::createSprite("PlayerSprite", "eagle");
	attachComponent(renderer);

	this->collider = new Collider("PlayerCollider");
	this->collider->setLocalBounds(sprite->getGlobalBounds());
	this->collider->setCollisionListener(this);
	this->attachComponent(this->collider);
}

void AirplanePlayer::processInputs(sf::Event event) {
	AbstractGameObject::processInputs(event);
}

void AirplanePlayer::update(sf::Time deltaTime) {
	AbstractGameObject::update(deltaTime); 
}

void AirplanePlayer::onCollisionEnter(AbstractGameObject* contact) {
	if (contact->getName().find("enemy") != std::string::npos) {
		std::cout << "AirplanePlayer collided with enemyGroundUnit" << std::endl;
	}
	else if (contact->getName().find("enemyGroundUnit") != std::string::npos) {
		std::cout << "AirplanePlayer collided with EnemyAirplane" << std::endl;
	}
}

void AirplanePlayer::onCollisionExit(AbstractGameObject* gameObject) {
	// Handle collision exit if needed
}
