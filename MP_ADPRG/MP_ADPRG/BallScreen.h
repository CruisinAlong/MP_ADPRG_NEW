// BallScreen.h
#pragma once
#include "BGObject.h"
#include "AirplanePlayer.h"
#include "AbstractGameObject.h"
#include "ButtonListener.h"
#include "UIData.h"

class BallScreen : public AbstractGameObject, public ButtonListener {
public:
    BallScreen(std::string name);
    void initialize() override;
    void onButtonClick(UIButton* button) override;
    void onButtonReleased(UIButton* button) override;

private:
    BGObject* bgObject;
    AirplanePlayer* player;
    UIText* scoreText;
    UIData* scoreData;
};
