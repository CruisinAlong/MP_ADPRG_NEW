// ConfirmationScreen.cpp
#include "ConfirmationScreen.h"

ConfirmationScreen::ConfirmationScreen(std::string name) : AbstractGameObject(name), ButtonListener() {}

void ConfirmationScreen::initialize() {
    std::cout << "ConfirmationScreen initialize called for: " << this->getName() << std::endl;

    sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("btn_normal");
    sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("btn_pressed");

    confirmationText = new UIText("ConfirmationText");
    this->attachChild(confirmationText);
    confirmationText->setPosition(0, -50);
    confirmationText->setSize(25);
    confirmationText->setText("Are you sure you want to quit?");

    yesButton = new UIButton("YesButton", btnNormal, btnPressed);
    this->attachChild(yesButton);
    yesButton->setPosition(-50, 50);
    yesButton->getTransformable()->setScale(0.3f, 0.3f);
    yesButton->setButtonListener(this);

    yesButtonText = new UIText("YesButtonText");
    yesButton->attachChild(yesButtonText);
    yesButtonText->setPosition(0, -20);
    yesButtonText->setSize(100);
    yesButtonText->setText("Yes");

    noButton = new UIButton("NoButton", btnNormal, btnPressed);
    this->attachChild(noButton);
    noButton->setPosition(50, 50);
    noButton->getTransformable()->setScale(0.3f, 0.3f);
    noButton->setButtonListener(this);

    noButtonText = new UIText("NoButtonText");
    noButton->attachChild(noButtonText);
    noButtonText->setPosition(0, -20);
    noButtonText->setSize(100);
    noButtonText->setText("No");
}

void ConfirmationScreen::onButtonClick(UIButton* button) {
    std::cout << button->getName() << " clicked" << std::endl;
    if (button->getName() == "YesButton") {
        // Quit the game
        ApplicationManager::getInstance()->applicationQuit();
    }
    else if (button->getName() == "NoButton") {
        ApplicationManager::getInstance()->resumeApplication(); 
        this->setEnabled(false);
    }
}

void ConfirmationScreen::onButtonReleased(UIButton* button) {
    std::cout << button->getName() << " released" << std::endl;
}

