// TitleScreen.cpp
#include "TitleScreen.h"

TitleScreen::TitleScreen(std::string name) : AbstractGameObject(name), ButtonListener(), showConfirmationPopup(false) {}

void TitleScreen::initialize() {
    std::cout << "TitleScreen initialize called for: " << this->getName() << std::endl;

    bgSprite = new sf::Sprite();
    bgSprite->setTexture(*TextureManager::getInstance()->getTexture("main_menu_bg"));
    sf::Vector2u textureSize = bgSprite->getTexture()->getSize();
    bgSprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

    Renderer* renderer = new Renderer("TitleScreen");
    renderer->assignDrawable(bgSprite);
    this->attachComponent(renderer);

    float posY = Game::WINDOW_HEIGHT / 2;
    float posX = Game::WINDOW_WIDTH / 2;
    this->setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);
    this->transformable.setScale(sf::Vector2f(0.7f, 0.7f));

    sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("btn_normal");
    sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("btn_pressed");

    playButton = new UIButton("PlayButton", btnNormal, btnPressed);
    this->attachChild(playButton);
    playButton->setPosition(0, -50);
    playButton->getTransformable()->setScale(0.3f, 0.3f);
    playButton->setButtonListener(this);

    UIText* playButtonText = new UIText("PlayButtonText");
    playButton->attachChild(playButtonText);
    playButtonText->setPosition(0, -20);
    playButtonText->setSize(100);
    playButtonText->setText("Play");

    quitButton = new UIButton("QuitButton", btnNormal, btnPressed);
    this->attachChild(quitButton);
    quitButton->setPosition(0, 50);
    quitButton->getTransformable()->setScale(0.3f, 0.3f);
    quitButton->setButtonListener(this);

    UIText* quitButtonText = new UIText("QuitButtonText");
    quitButton->attachChild(quitButtonText);
    quitButtonText->setPosition(0, -20);
    quitButtonText->setSize(100);
    quitButtonText->setText("Quit");

    /* Confirmation popup elements
    confirm = new ConfirmationScreen("ConfirmationScreen");
	GameObjectManager::getInstance()->addObject(confirm); 

    confirmationText = new UIText("ConfirmationText");
    this->attachChild(confirmationText);
    confirmationText->setPosition(0, -150);
    confirmationText->setSize(25);
    confirmationText->setText("Are you sure you want to quit?");
    confirmationText->setEnabled(false);

    yesButton = new UIButton("YesButton", btnNormal, btnPressed);
    this->attachChild(yesButton);
    yesButton->setPosition(-50, 0);
    yesButton->getTransformable()->setScale(0.3f, 0.3f);
    yesButton->setButtonListener(this);
    yesButton->setEnabled(false);

    UIText* yesButtonText = new UIText("YesButtonText");
    yesButton->attachChild(yesButtonText);
    yesButtonText->setPosition(0, -20);
    yesButtonText->setSize(100);
    yesButtonText->setText("Yes");
    yesButtonText->setEnabled(false);

    noButton = new UIButton("NoButton", btnNormal, btnPressed);
    this->attachChild(noButton);
    noButton->setPosition(50, 0);
    noButton->getTransformable()->setScale(0.3f, 0.3f);
    noButton->setButtonListener(this);
    noButton->setEnabled(false);

    UIText* noButtonText = new UIText("NoButtonText");
    noButton->attachChild(noButtonText);
    noButtonText->setPosition(0, -20);
    noButtonText->setSize(100);
    noButtonText->setText("No");
    noButtonText->setEnabled(false); */
}

void TitleScreen::onButtonClick(UIButton* button) {
    std::cout << button->getName() << " clicked" << std::endl;
    if (button->getName() == "PlayButton") {
        SceneManager::getInstance()->loadScene("BallScene");
        ApplicationManager::getInstance()->resumeApplication();
    }
    else if (button->getName() == "QuitButton") {
        ApplicationManager::getInstance()->applicationQuit();
    }

}

void TitleScreen::onButtonReleased(UIButton* button) {
    std::cout << button->getName() << " released" << std::endl;
}


