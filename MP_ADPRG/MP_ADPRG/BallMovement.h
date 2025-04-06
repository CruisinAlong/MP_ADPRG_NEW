// BallMovement.h
#pragma once

#include "AbstractComponent.h"
#include "BallObject.h"

class BallMovement : public AbstractComponent {
public:
    BallMovement(std::string name);
    void perform() override;
    void setPlayerOnTop(bool onTop);

private:
    bool playerOnTop;
    float moveSpeed;
};

