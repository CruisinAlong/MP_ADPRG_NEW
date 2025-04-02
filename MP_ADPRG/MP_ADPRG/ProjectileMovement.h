#pragma once
#include "AbstractComponent.h"
class ProjectileMovement : public AbstractComponent {
public:
	ProjectileMovement(std::string name);
	void perform();
	void reset();
private:
	const float SPEED_MULTIPLIER = 240.0f;
	float ticks = 0.0f;
};