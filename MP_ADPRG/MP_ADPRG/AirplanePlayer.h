#pragma once
#include "AbstractGameObject.h"
#include "PlayerInputController.h"
#include "PlayerMovement.h"
#include "Renderer.h"
#include "PhysicsManager.h"
#include <iostream>
#include "TextureManager.h"
#include "Collider.h"
#include "Game.h"

class AirplanePlayer : public AbstractGameObject, public CollisionListener
{
public:
	AirplanePlayer(std::string name);
	void initialize() override;
	void update(sf::Time deltaTime);
	void processInputs(sf::Event event) override;

	void onCollisionEnter(AbstractGameObject* contact) override;
	void onCollisionExit(AbstractGameObject* gameObject) override;
	void checkPositions();
	
private:
	const float SPEED_MULTIPLIER = 300.f;
	bool moveUp = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;
	Collider* collider;
	float direction = 1.0f;
	sf::RectangleShape debugShape;
};