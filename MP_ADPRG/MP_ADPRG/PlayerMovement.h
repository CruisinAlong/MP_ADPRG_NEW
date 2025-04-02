#pragma once
#include "AbstractComponent.h"
#include "AirplanePlayer.h"
#include "PlayerInputController.h"
#include "ObjectPoolHolder.h"
#include "GameObjectPool.h"
#include <iostream>
#include <string>

class PlayerMovement : public AbstractComponent {
public:
	PlayerMovement(std::string name);
	void perform();
private:
	GameObjectPool* projectilePool;
	const float SPEED_MULTIPLIER = 300.0f;
	const float BULLET_SPAWN_INTERVAL = 2.0f;
	float ticks = 0.0f;

	bool isJumping;
	float jumpSpeed;
	float gravity;
	float velocityY;
	float playerHeight;
};