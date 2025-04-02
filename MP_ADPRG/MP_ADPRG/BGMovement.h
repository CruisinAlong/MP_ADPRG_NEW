#pragma once
#include "AbstractComponent.h"
#include "BGInputController.h" 

class BGMovement : public AbstractComponent {
public:
    BGMovement(std::string name);
    ~BGMovement(); 
    void perform() override;
    void setInputController(BGInputController* inputController); 
    bool isMoving() const;

private:
    const float SPEED = 50.f;
    BGInputController* inputController = nullptr; 
    bool moving = false;
};

