// FastJumpingEnemy.cpp
#include "FastJumpingEnemy.h"
#include "TextureManager.h"
#include "Game.h"
#include "Renderer.h"
#include "EnemyBehavior.h"
#include "UIManager.h"
#include <iostream>
#include "MonkeyLevelScreen.h"

FastJumpingEnemy::FastJumpingEnemy(std::string name) : AbstractPoolable(name), CollisionListener(), sprite(nullptr), collider(nullptr), hasJumped(false) {}
/// <summary>
/// Fast monkey enemy
/// </summary>
void FastJumpingEnemy::initialize() {
    this->sprite = new sf::Sprite();
    sprite->setTexture(*TextureManager::getInstance()->getTexture("monkey"));
    sf::Vector2u textureSize = sprite->getTexture()->getSize();
    sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

    this->setPosition(Game::WINDOW_WIDTH + static_cast<int>(textureSize.x) / 2, Game::WINDOW_HEIGHT - static_cast<int>(textureSize.y) / 2);
    this->getTransformable()->move(rand() % 300, 0);
    this->getTransformable()->setRotation(0);

    Renderer* renderer = new Renderer("FastJumpingEnemySprite");
    renderer->assignDrawable(sprite);
    this->attachComponent(renderer);

    EnemyBehavior* behavior = new EnemyBehavior("FastJumpingEnemyBehavior");
    this->attachComponent(behavior);
    behavior->configure(EnemyBehavior::FastJump);

    this->collider = new Collider("FastJumpingEnemyCollider"); 
    this->collider->setLocalBounds(sprite->getGlobalBounds()); 
    this->collider->setCollisionListener(this); 
    this->attachComponent(this->collider); 

    std::cout << "BOUNDS: " << sprite->getGlobalBounds().left << ":" << sprite->getGlobalBounds().top << ":" << sprite->getGlobalBounds().width << ":" << sprite->getGlobalBounds().height << std::endl;
}

void FastJumpingEnemy::onRelease() {
    PhysicsManager::getInstance()->untrackObject(this->collider);
}

void FastJumpingEnemy::onActivate() {
    EnemyBehavior* behaviour = (EnemyBehavior*)this->findComponentByName("FastJumpingEnemyBehavior");
    behaviour->reset();

    PhysicsManager::getInstance()->trackObject(this->collider);

    this->setPosition(Game::WINDOW_WIDTH + static_cast<int>(sprite->getTexture()->getSize().x) / 2, Game::WINDOW_HEIGHT - static_cast<int>(sprite->getTexture()->getSize().y) / 2);
}

AbstractPoolable* FastJumpingEnemy::clone() {
    AbstractPoolable* copyObj = new FastJumpingEnemy(this->name);
    return copyObj;
}

void FastJumpingEnemy::update(sf::Time deltaTime) {
    AbstractGameObject::update(deltaTime);
}

void FastJumpingEnemy::onCollisionEnter(AbstractGameObject* contact) {
    if (!collisionProcessed && contact->getName().find("PlaneObject") != std::string::npos) {
        collisionProcessed = true;
        std::cout << "FastJumpingEnemy collided with PlaneObject" << std::endl;
        UIData* scoreData = UIManager::getInstance()->getUIData(UIManager::SCORE_UI_KEY);
        scoreData->putInt(UIManager::SCORE_UI_KEY, scoreData->getInt(UIManager::SCORE_UI_KEY, 0) - 100);
        scoreData->refreshTextFromData("scoreText", UIManager::SCORE_UI_KEY, "Score: ");
        MonkeyLevelScreen* monkeyLevelScreen = dynamic_cast<MonkeyLevelScreen*>(this->getParent());
        if (monkeyLevelScreen) {
            monkeyLevelScreen->activateCooldown(); 
        }
    }
}

void FastJumpingEnemy::onCollisionExit(AbstractGameObject* gameObject) {
    collisionProcessed = false;
}



