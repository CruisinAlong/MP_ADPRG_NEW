#include "SlowForwardEnemy.h"
#include "TextureManager.h"
#include "Game.h"
#include "Renderer.h"
#include "EnemyBehavior.h"
#include "UIManager.h"
#include <iostream>
#include "MonkeyLevelScene.h"

SlowForwardEnemy::SlowForwardEnemy(std::string name) : AbstractPoolable(name), CollisionListener(), sprite(nullptr), collider(nullptr) {}

void SlowForwardEnemy::initialize() {
    this->sprite = new sf::Sprite();
    sprite->setTexture(*TextureManager::getInstance()->getTexture("monkey"));
    sf::Vector2u textureSize = sprite->getTexture()->getSize();
    sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

    this->setPosition(Game::WINDOW_WIDTH + static_cast<int>(textureSize.x) / 2, Game::WINDOW_HEIGHT - static_cast<int>(textureSize.y) / 2);
    this->getTransformable()->move(rand() % 300, 0);
    this->getTransformable()->setRotation(0);

    Renderer* renderer = new Renderer("SlowForwardEnemySprite");
    renderer->assignDrawable(sprite);
    this->attachComponent(renderer);

    EnemyBehavior* behavior = new EnemyBehavior("SlowForwardEnemyBehavior");
    this->attachComponent(behavior);
    behavior->configure(EnemyBehavior::SlowForward);

    this->collider = new Collider("SlowForwardEnemyCollider");
    this->collider->setLocalBounds(sprite->getGlobalBounds());
    this->collider->setCollisionListener(this);
    this->attachComponent(this->collider);

    std::cout << "BOUNDS: " << sprite->getGlobalBounds().left << ":" << sprite->getGlobalBounds().top << ":" << sprite->getGlobalBounds().width << ":" << sprite->getGlobalBounds().height << std::endl;
}

void SlowForwardEnemy::onRelease() {
    PhysicsManager::getInstance()->untrackObject(this->collider);
}

void SlowForwardEnemy::onActivate() {
    EnemyBehavior* behaviour = (EnemyBehavior*)this->findComponentByName("SlowForwardEnemyBehavior");
    behaviour->reset();

    PhysicsManager::getInstance()->trackObject(this->collider);

    this->setPosition(Game::WINDOW_WIDTH + static_cast<int>(sprite->getTexture()->getSize().x) / 2, Game::WINDOW_HEIGHT - static_cast<int>(sprite->getTexture()->getSize().y) / 2);
}

AbstractPoolable* SlowForwardEnemy::clone() {
    AbstractPoolable* copyObj = new SlowForwardEnemy(this->name);
    return copyObj;
}

void SlowForwardEnemy::update(sf::Time deltaTime) {
    AbstractGameObject::update(deltaTime);
}

void SlowForwardEnemy::onCollisionEnter(AbstractGameObject* contact) {
    if (!collisionProcessed && contact->getName().find("PlaneObject") != std::string::npos) {
        collisionProcessed = true;
        std::cout << "SlowForwardEnemy collided with PlaneObject" << std::endl;
        UIData* scoreData = UIManager::getInstance()->getUIData(UIManager::SCORE_UI_KEY);
        scoreData->putInt(UIManager::SCORE_UI_KEY, scoreData->getInt(UIManager::SCORE_UI_KEY, 0) - 100);
        scoreData->refreshTextFromData("scoreText", UIManager::SCORE_UI_KEY, "Score: ");
        MonkeyLevelScreen* monkeyLevelScreen = dynamic_cast<MonkeyLevelScreen*>(this->getParent());
        if (monkeyLevelScreen) {
            monkeyLevelScreen->activateCooldown();
        }
    }
}

void SlowForwardEnemy::onCollisionExit(AbstractGameObject* gameObject) {
    collisionProcessed = false;
}
