#pragma once
#include "AbstractGameObject.h"
#include "UIButton.h"
#include "UIText.h"
#include "GameObjectManager.h"
#include "TextureManager.h"
#include "ApplicationManager.h"
#include <iostream>

class ConfirmationScreen : public AbstractGameObject, public ButtonListener {
public:
    ConfirmationScreen(std::string name);
    void initialize() override;
    void onButtonClick(UIButton* button) override;
    void onButtonReleased(UIButton* button) override;

private:
    UIText* confirmationText;
    UIButton* yesButton;
    UIButton* noButton;
    UIText* yesButtonText;
    UIText* noButtonText;
};


