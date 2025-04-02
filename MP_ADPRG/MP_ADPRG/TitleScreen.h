#pragma once
#include "AbstractGameObject.h"
#include "UIButton.h"
#include "UIText.h"
#include "GameObjectManager.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include "Game.h"
#include "ConfirmationScreen.h"
#include <iostream>

class TitleScreen : public AbstractGameObject, public ButtonListener {
public:
    TitleScreen(std::string name);
    void initialize() override;
    void onButtonClick(UIButton* button) override;
    void onButtonReleased(UIButton* button) override;

private:
    sf::Sprite* bgSprite;
    UIButton* playButton;
    UIButton* quitButton;
    UIText* confirmationText;
    UIButton* yesButton;
    UIButton* noButton;
    UIText* yesButtonText;
    UIText* noButtonText;
    bool showConfirmationPopup;
	ConfirmationScreen* confirm;
};


