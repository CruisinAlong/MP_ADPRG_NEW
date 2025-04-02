#pragma once
#include "AbstractGameObject.h"
#include "UIButton.h"
#include "UIText.h"

class MainMenuScreen : public AbstractGameObject, public ButtonListener {
public:
    MainMenuScreen(std::string name);
    void initialize() override;
    void onButtonClick(UIButton* button) override;
    void onButtonReleased(UIButton* button) override;

private:
    sf::Sprite* bgSprite;
    UIButton* playButton;
    UIButton* quitButton;
    UIButton* yesButton;
    UIButton* noButton;
    UIText* confirmationText;
    bool showConfirmationPopup;
};
