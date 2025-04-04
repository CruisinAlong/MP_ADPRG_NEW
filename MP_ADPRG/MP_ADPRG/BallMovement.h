// BallMovement.h
#pragma once

#include "AbstractComponent.h"

class BallMovement : public AbstractComponent {
public:
    BallMovement(std::string name);
    void perform() override;
};
