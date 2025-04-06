#include "BallObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "Renderer.h"
#include "BallPlayer.h"
#include "EnemyBehavior.h"

BallObject::BallObject(std::string name) : AbstractPoolable(name), CollisionListener(), collisionHandled(false) {
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
    behavior->configure(EnemyBehavior::SlowForward);
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
    collisionHandled = false;
}



AbstractPoolable* BallObject::clone() {
    AbstractPoolable* copyObj = new BallObject(this->name);
    return copyObj;
}

void BallObject::onCollisionEnter(AbstractGameObject* contact) {
    if (collisionHandled) {
        return;
    }

    if (contact->getName().find("PlayerObject") != std::string::npos) {
        std::cout << "BallObject collided with PlayerObject" << std::endl;
        BallPlayer* player = dynamic_cast<BallPlayer*>(contact);
        if (player != nullptr) {

            std::cout << "BallObject set under PlayerObject at position: " << this->getTransformable()->getPosition().x << ", " << this->getTransformable()->getPosition().y << std::endl;
            // Configure the BallObject to stop moving
            EnemyBehavior* behavior = dynamic_cast<EnemyBehavior*>(this->findComponentByName("BallBehavior"));
            if (behavior != nullptr) {
                behavior->configure(EnemyBehavior::NonMoving);
            }

            UIData* scoreData = UIManager::getInstance()->getUIData(UIManager::SCORE_UI_KEY);
            scoreData->putInt(UIManager::SCORE_UI_KEY, scoreData->getInt(UIManager::SCORE_UI_KEY, 0) + 100);
            scoreData->refreshTextFromData("scoreText", UIManager::SCORE_UI_KEY, "Score: ");

            collisionHandled = true; 
        }
    }
}

void BallObject::onCollisionExit(AbstractGameObject* gameObject) {
    EnemyBehavior* behavior = dynamic_cast<EnemyBehavior*>(this->findComponentByName("BallBehavior"));
    behavior->configure(EnemyBehavior::SlowForward);
}

sf::Sprite* BallObject::getSprite() const {
    return sprite;
}
