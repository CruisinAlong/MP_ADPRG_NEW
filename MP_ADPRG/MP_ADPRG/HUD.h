#pragma once
#include "AbstractGameObject.h"
#include "UIButton.h"
#include "UIText.h"

class HUD : public AbstractGameObject, public ButtonListener {
public:
    HUD(std::string name);
    void initialize() override;
    void onButtonClick(UIButton* button) override;
    void onButtonReleased(UIButton* button) override;

private:
    UIButton* quitButton;
    UIText* quitButtonText;
    UIText* confirmationText;
    UIButton* yesButton;
    UIButton* noButton;
    UIText* yesButtonText;
    UIText* noButtonText;
};
