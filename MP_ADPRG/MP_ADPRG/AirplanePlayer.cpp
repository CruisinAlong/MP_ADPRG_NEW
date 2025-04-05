#include "AirplanePlayer.h"



AirplanePlayer::AirplanePlayer(std::string name) : AbstractGameObject(name), CollisionListener()
{
}


void AirplanePlayer::initialize()
{
	std::cout << "AirplanePlayer initialized" << std::endl;

	if (PhysicsManager::getInstance() == nullptr) {
		std::cout << "Creating PhysicsManager" << std::endl;
		PhysicsManager::initialize("PhysicsManager", this);
	}

	this->transformable.setPosition(Game::WINDOW_WIDTH / 4, Game::WINDOW_HEIGHT - 30);

	PlayerInputController* inputController = new PlayerInputController("MyPlayerInput");
	this->attachComponent(inputController);



	PlayerMovement* movement = new PlayerMovement("MyMovement");
	this->attachComponent(movement);

	Renderer* renderer = Renderer::createSprite("PlayerSprite", "eagle");
	attachComponent(renderer);

	sf::Sprite* sprite = renderer->getSprite(); // Retrieve the sprite
	if (sprite != nullptr) {
		std::cout << "Position: " << sprite->getPosition().x << ":" << sprite->getPosition().y << std::endl;
		this->collider = new Collider("PlayerCollider");
		this->collider->setLocalBounds(sprite->getGlobalBounds());
		std::cout << "BOUNDS: " << sprite->getGlobalBounds().left << ":" << sprite->getGlobalBounds().top << ":" << sprite->getGlobalBounds().width << ":" << sprite->getGlobalBounds().height << std::endl;
	}
	else {
		std::cerr << "Error: sprite is nullptr" << std::endl;
	}
	this->collider->setCollisionListener(this);
	this->attachComponent(this->collider);

	PhysicsManager* physicsManager = PhysicsManager::getInstance();
	if (physicsManager != nullptr) {
		physicsManager->trackObject(this->collider);
	}
	else {
		std::cerr << "Error: PhysicsManager instance is not initialized." << std::endl;
	}
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
