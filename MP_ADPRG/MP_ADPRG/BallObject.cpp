#include "BallObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "Renderer.h"
#include "EnemyBehavior.h"

BallObject::BallObject(std::string name) : AbstractPoolable(name), CollisionListener() {
}

void BallObject::initialize() {

    this->sprite = new sf::Sprite();
    sprite->setTexture(*TextureManager::getInstance()->getTexture("avenger"));
    sf::Vector2u textureSize = sprite->getTexture()->getSize();
    sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

    this->setPosition(Game::WINDOW_WIDTH + static_cast<int>(textureSize.x) / 2, Game::WINDOW_HEIGHT - static_cast<int>(textureSize.y) / 2);
    this->getTransformable()->setRotation(0);

    Renderer* renderer = new Renderer("BallSprite");
    renderer->assignDrawable(sprite);
    this->attachComponent(renderer);

    EnemyBehavior* behavior = new EnemyBehavior("BallBehavior");
    this->attachComponent(behavior);
    behavior->configure(EnemyBehavior::Static);
    EnemyInputController* inputController = new EnemyInputController("BallInputController");
    this->attachComponent(inputController);

    this->collider = new Collider("BallCollider");
    this->collider->setLocalBounds(sprite->getGlobalBounds());
    this->collider->setCollisionListener(this);
    this->attachComponent(this->collider);

    behavior->setInputController(inputController);
    std::cout << "BOUNDS: " << sprite->getGlobalBounds().left << ":" << sprite->getGlobalBounds().top << ":" << sprite->getGlobalBounds().width << ":" << sprite->getGlobalBounds().height << std::endl;
}

void BallObject::onRelease() {
    PhysicsManager::getInstance()->untrackObject(this->collider);
}

void BallObject::onActivate() {
    EnemyBehavior* behaviour = (EnemyBehavior*)this->findComponentByName("BallBehavior");
    behaviour->reset();

    PhysicsManager::getInstance()->trackObject(this->collider);

    this->setPosition(Game::WINDOW_WIDTH + static_cast<int>(sprite->getTexture()->getSize().x) / 2, Game::WINDOW_HEIGHT - static_cast<int>(sprite->getTexture()->getSize().y) / 2);
}

AbstractPoolable* BallObject::clone() {
    AbstractPoolable* copyObj = new BallObject(this->name);
    return copyObj;
}

void BallObject::onCollisionEnter(AbstractGameObject* contact) {
    if (contact->getName().find("PlaneObject") != std::string::npos) {
        std::cout << "BallObject collided with PlaneObject" << std::endl;
        UIData* scoreData = UIManager::getInstance()->getUIData(UIManager::SCORE_UI_KEY);
        scoreData->putInt(UIManager::SCORE_UI_KEY, scoreData->getInt(UIManager::SCORE_UI_KEY, 0) + 100);
        scoreData->refreshTextFromData("scoreText", UIManager::SCORE_UI_KEY, "Score: ");
    }
}

void BallObject::onCollisionExit(AbstractGameObject* gameObject) {
}
