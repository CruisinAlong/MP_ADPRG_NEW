// BallScreen.h
#pragma once

#include "AbstractGameObject.h"
#include "ButtonListener.h"

class BallScreen : public AbstractGameObject, public ButtonListener {
public:
    BallScreen(std::string name);
    void initialize() override;
    void onButtonClick(UIButton* button) override;
    void onButtonReleased(UIButton* button) override;

private:
    BGObject* bgObject;
    AirplanePlayer* player;
};
