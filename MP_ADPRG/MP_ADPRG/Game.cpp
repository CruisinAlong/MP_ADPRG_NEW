#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "BallScene.h"
#include "MonkeyLevelScene.h"

Game::Game() : mWindow(sf::VideoMode(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT), "SFML Application") {
    std::cout << "Game constructor called" << std::endl;
    mWindow.setFramerateLimit(60);
    TextureManager::getInstance()->loadAll();
    FontManager::getInstance()->loadAll();
    SoundManager::getInstance()->loadAll();



    SceneManager::getInstance()->registerScene(new TitleScene());
    SceneManager::getInstance()->registerScene(new MainMenuScene());
    SceneManager::getInstance()->registerScene(new GameScene());
    SceneManager::getInstance()->registerScene(new BallScene());
    SceneManager::getInstance()->registerScene(new MonkeyLevelScene());
    SceneManager::getInstance()->loadScene("TitleScene");
}

void Game::addEntity(std::string key, float x, float y) {
    sf::Texture* tex = TextureManager::getInstance()->getTexture(key);
    Entity* entity = Entity::createEntity(tex, x, y);
    mEntitiyList.push_back(entity);
}

void Game::run() {
    std::cout << "Game run started" << std::endl;
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen()) {
        sf::Time deltaTime = clock.restart();
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }

        update(deltaTime);
        render();
        SceneManager::getInstance()->checkLoadScene();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            std::cout << "Window closed event" << std::endl;
            mWindow.close();
            break;
        default:
            GameObjectManager::getInstance()->processInput(event);
            break;
        }
    }
}

void Game::render() {
    mWindow.clear();
    GameObjectManager::getInstance()->draw(&mWindow);
    mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    switch (key) {
    case sf::Keyboard::W:
        mIsMovingUp = isPressed;
        break;
    case sf::Keyboard::S:
        mIsMovingDown = isPressed;
        break;
    case sf::Keyboard::A:
        mIsMovingLeft = isPressed;
        break;
    case sf::Keyboard::D:
        mIsMovingRight = isPressed;
        break;
    }
}

void Game::update(sf::Time deltaTime) {
    if (!ApplicationManager::getInstance()->isPaused()) {
        GameObjectManager::getInstance()->update(deltaTime);
    }
}
