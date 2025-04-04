#pragma once
#include "AbstractComponent.h"
#include "EnemyInputController.h"

class EnemyBehavior : public AbstractComponent {
public:
	enum EnemyMovementType { Static = 0, SlowForward = 1 };

	EnemyBehavior(std::string name);
	void perform() override;
	void configure(EnemyMovementType type, float delay = 0.0f);
	void reset();
	void setInputController(EnemyInputController* inputController);



private:
	const float SPEED_MULTIPLIER = 100.0f;
	EnemyBehavior::EnemyMovementType movementType = Static;
	float ticks = 0.0f;
	float delay = 0.0f;
	float forwardDuration = 0.0f;
	EnemyInputController* inputController = nullptr; 
};