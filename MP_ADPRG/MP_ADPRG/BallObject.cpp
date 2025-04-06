// BallObject.cpp
#include "BallObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "Renderer.h"
#include "BallPlayer.h"
#include "EnemyBehavior.h"

/// <summary>
/// Constructor for BallObject
/// </summary>
/// <param name="name">The name of the ball object</param>
BallObject::BallObject(std::string name) : AbstractPoolable(name), CollisionListener(), collisionHandled(false) {}

/// <summary>
/// Initialize the BallObject
/// </summary>
void BallObject::initialize() {
    // Create and set up the sprite
    this->sprite = new sf::Sprite();
    sprite->setTexture(*TextureManager::getInstance()->getTexture("ball"));
    sf::Vector2u textureSize = sprite->getTexture()->getSize();
    sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

    // Set the initial position of the ball
    this->setPosition(Game::WINDOW_WIDTH + static_cast<int>(textureSize.x) / 2, Game::WINDOW_HEIGHT - static_cast<int>(textureSize.y) / 2);
    this->getTransformable()->setRotation(0);

    // Attach renderer component
    Renderer* renderer = new Renderer("BallSprite");
    renderer->assignDrawable(sprite);
    this->attachComponent(renderer);

    // Attach behavior component
    EnemyBehavior* behavior = new EnemyBehavior("BallBehavior");
    this->attachComponent(behavior);
    behavior->configure(EnemyBehavior::SlowForward);

    // Attach input controller component
    EnemyInputController* inputController = new EnemyInputController("BallInputController");
    this->attachComponent(inputController);

    // Attach collider component
    this->collider = new Collider("BallCollider");
    this->collider->setLocalBounds(sprite->getGlobalBounds());
    this->collider->setCollisionListener(this);
    this->attachComponent(this->collider);

    // Set the input controller for the behavior
    behavior->setInputController(inputController);

    std::cout << "BOUNDS: " << sprite->getGlobalBounds().left << ":" << sprite->getGlobalBounds().top << ":" << sprite->getGlobalBounds().width << ":" << sprite->getGlobalBounds().height << std::endl;
}

/// <summary>
/// Handle the release of the BallObject
/// </summary>
void BallObject::onRelease() {
    PhysicsManager::getInstance()->untrackObject(this->collider);
}

/// <summary>
/// Handle the activation of the BallObject
/// </summary>
void BallObject::onActivate() {
    // Reset the behavior
    EnemyBehavior* behaviour = (EnemyBehavior*)this->findComponentByName("BallBehavior");
    behaviour->reset();

    // Track the collider with the PhysicsManager
    PhysicsManager::getInstance()->trackObject(this->collider);

    // Set the initial position of the ball
    this->setPosition(Game::WINDOW_WIDTH + static_cast<int>(sprite->getTexture()->getSize().x) / 2, Game::WINDOW_HEIGHT - static_cast<int>(sprite->getTexture()->getSize().y) / 2);
    collisionHandled = false;
}

/// <summary>
/// Clone the BallObject
/// </summary>
/// <returns>A copy of the BallObject</returns>
AbstractPoolable* BallObject::clone() {
    AbstractPoolable* copyObj = new BallObject(this->name);
    return copyObj;
}

/// <summary>
/// Handle collision enter events
/// </summary>
/// <param name="contact">The game object that the ball collided with</param>
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

            // Update the score
            UIData* scoreData = UIManager::getInstance()->getUIData(UIManager::SCORE_UI_KEY);
            scoreData->putInt(UIManager::SCORE_UI_KEY, scoreData->getInt(UIManager::SCORE_UI_KEY, 0) + 100);
            scoreData->refreshTextFromData("scoreText", UIManager::SCORE_UI_KEY, "Score: ");

            collisionHandled = true;
        }
    }
}

/// <summary>
/// Handle collision exit events
/// </summary>
/// <param name="gameObject">The game object that the ball stopped colliding with</param>
void BallObject::onCollisionExit(AbstractGameObject* gameObject) {
    // Configure the BallObject to start moving again
    EnemyBehavior* behavior = dynamic_cast<EnemyBehavior*>(this->findComponentByName("BallBehavior"));
    behavior->configure(EnemyBehavior::SlowForward);
}

/// <summary>
/// Get the sprite of the BallObject
/// </summary>
/// <returns>The sprite of the BallObject</returns>
sf::Sprite* BallObject::getSprite() const {
    return sprite;
}

