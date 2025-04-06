#pragma once
#include "AbstractComponent.h"
#include "BGInputController.h" 

class BGMovement : public AbstractComponent {
public:
    BGMovement(std::string name);
    void perform() override;
    void setInputController(BGInputController* inputController); 
    bool isMoving() const;
    bool isLevelFinished();

private:
    const float SPEED = 50.f;
    float LEVEL_END_DISTANCE;
    BGInputController* inputController = nullptr;
    bool moving = false; 
    float distanceTraveled = 0.0f; 
    bool levelFinished = false; 
};

