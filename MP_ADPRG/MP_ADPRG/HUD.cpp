#include "HUD.h"
#include "TextureManager.h"
#include "Game.h"
#include "Renderer.h"
#include "GameObjectManager.h"
#include "MainMenuScreen.h"
#include <iostream>

HUD::HUD(std::string name) : AbstractGameObject(name), ButtonListener() {}

void HUD::initialize() {
    std::cout << "HUD initialize called for: " << this->getName() << std::endl;

    sf::Sprite* sprite = new sf::Sprite();
    sprite->setTexture(*TextureManager::getInstance()->getTexture("HUD_bg"));
    sf::Vector2u textureSize = sprite->getTexture()->getSize();
    sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

    Renderer* renderer = new Renderer("HUD");
    renderer->assignDrawable(sprite);
    this->attachComponent(renderer);

    float posX = Game::WINDOW_WIDTH - textureSize.x / 2;
    float posY = textureSize.y / 2;
    this->setPosition(posX, posY);

    sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("btn_normal");
    sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("btn_pressed");

    quitButton = new UIButton("quit_button", btnNormal, btnPressed);
    this->attachChild(quitButton);
    quitButton->setPosition(textureSize.x / 2 - 70, textureSize.y / 2 - 32);
    quitButton->getTransformable()->setScale(0.2f, 0.2f);
    quitButton->setButtonListener(this);

    quitButtonText = new UIText("quit_button_text");
    quitButton->attachChild(quitButtonText);
    quitButtonText->setPosition(0, -10);
    quitButtonText->setSize(75);
    quitButtonText->setText("QUIT");
}

void HUD::onButtonClick(UIButton* button) {
    if (button->getName() == "quit_button") {
        std::cout << "Quit button clicked" << std::endl;
        // Enable the main menu
        MainMenuScreen* mainMenu = dynamic_cast<MainMenuScreen*>(GameObjectManager::getInstance()->findObjectByName("MainMenu"));
        if (mainMenu) {
            mainMenu->setEnabled(true);
        }
        ApplicationManager::getInstance()->pauseApplication();
    }
}

void HUD::onButtonReleased(UIButton* button) {
    if (button->getName() == "quit_button") {
        std::cout << "Quit button released" << std::endl;
    }
}
