#pragma once
#include "AbstractComponent.h"
class AirplaneSupportMovement : public AbstractComponent {
public:
	AirplaneSupportMovement(std::string name);
	void perform();
	bool moveLeft = false;
	bool moveRight = false;

private: 
	const float SPEED = 50.0f;
	float elapsedTime;
	float direction;
};