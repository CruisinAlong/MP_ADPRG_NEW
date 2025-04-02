// MainMenuScreen.cpp
#include "MainMenuScreen.h"
#include "TextureManager.h"
#include "Game.h"
#include "Renderer.h"
#include "GameObjectManager.h"
#include "ApplicationManager.h"
#include <iostream>
#include <string>

MainMenuScreen::MainMenuScreen(std::string name) : AbstractGameObject(name), ButtonListener(), showConfirmationPopup(false) {} 

void MainMenuScreen::initialize() {
    std::cout << "MainMenuScreen initialize called for: " << this->getName() << std::endl;

    bgSprite = new sf::Sprite();
    bgSprite->setTexture(*TextureManager::getInstance()->getTexture("title_bg"));
    sf::Vector2u textureSize = bgSprite->getTexture()->getSize();
    bgSprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

    Renderer* renderer = new Renderer("MainMenuScreen");
    renderer->assignDrawable(bgSprite);
    this->attachComponent(renderer);

    float posY = Game::WINDOW_HEIGHT / 2;
    float posX = Game::WINDOW_WIDTH / 2;
    this->setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);
    this->transformable.setScale(sf::Vector2f(0.7f, 0.7f));

    sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("btn_normal");
    sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("btn_pressed");

    // Add confirmation popup
    UIText* quitConfirmationText = new UIText("quit_confirmation_text");
    this->attachChild(quitConfirmationText);
    quitConfirmationText->setPosition(0, -150);
    quitConfirmationText->setSize(25);
    quitConfirmationText->setText("Are you sure you want to go to the main menu?");

    UIButton* button1 = new UIButton("button_1", btnNormal, btnPressed);
    this->attachChild(button1);
    button1->setPosition(0, -50);
    button1->getTransformable()->setScale(0.3f, 0.3f);
    button1->setButtonListener(this);

    std::cout << "Creating UIText for button_1" << std::endl;
    UIText* button_1Text = new UIText("text_1");
    button1->attachChild(button_1Text);
    button_1Text->setPosition(0, -20);
    button_1Text->setSize(100);
    button_1Text->setText("YES");

    UIButton* button2 = new UIButton("button_2", btnNormal, btnPressed);
    this->attachChild(button2);
    button2->setPosition(0, 50);
    button2->getTransformable()->setScale(0.3f, 0.3f);
    button2->setButtonListener(this);
    std::cout << "Creating UIText for button_2" << std::endl;
    UIText* button_2Text = new UIText("text_2");
    button2->attachChild(button_2Text);
    button_2Text->setPosition(0, -20);
    button_2Text->setSize(100);
    button_2Text->setText("NO");
}

void MainMenuScreen::onButtonClick(UIButton* button) {
    std::cout << button->getName() << " clicked" << std::endl;
    if (button->getName() == "button_1") {
        // Go back to the main menu
        SceneManager::getInstance()->loadScene("TitleScene");
        ApplicationManager::getInstance()->resumeApplication();  
    }
    else if (button->getName() == "button_2") {
        this->setEnabled(false); 
        ApplicationManager::getInstance()->resumeApplication(); 
    }
}

void MainMenuScreen::onButtonReleased(UIButton* button) {
    std::cout << button->getName() << " released" << std::endl;
}

