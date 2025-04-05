#include "AirplanePlayer.h"



AirplanePlayer::AirplanePlayer(std::string name) : AbstractGameObject(name), CollisionListener()
{
}


void AirplanePlayer::initialize()
{
	std::cout << "AirplanePlayer initialized" << std::endl;

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

	checkPositions();
}

void AirplanePlayer::processInputs(sf::Event event) {
	AbstractGameObject::processInputs(event);
}

void AirplanePlayer::update(sf::Time deltaTime) {
	AbstractGameObject::update(deltaTime); 
}

void AirplanePlayer::checkPositions() {
	// Get the position of the player
	sf::Vector2f playerPosition = this->transformable.getPosition();

	// Get the bounds of the collider
	sf::FloatRect colliderBounds = this->collider->getGlobalBounds();

	// Calculate the center position of the collider
	sf::Vector2f colliderCenter(colliderBounds.left + colliderBounds.width / 2, colliderBounds.top + colliderBounds.height / 2);

	// Compare the positions
	if (playerPosition == colliderCenter) {
		std::cout << "The positions match." << std::endl;
	}
	else {
		std::cout << "The positions do not match." << std::endl;
		std::cout << "Player Position: " << playerPosition.x << ", " << playerPosition.y << std::endl;
		std::cout << "Collider Center: " << colliderCenter.x << ", " << colliderCenter.y << std::endl;
	}
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
