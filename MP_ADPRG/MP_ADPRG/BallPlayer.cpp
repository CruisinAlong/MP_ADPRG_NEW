#include "BallPlayer.h"
#include "PhysicsManager.h"
#include "Renderer.h"
#include "PlayerInputController.h"
#include "PlayerBallMovement.h"
#include "TextureManager.h"
#include "EnemyBehavior.h"
#include "Game.h"

BallPlayer::BallPlayer(std::string name) : AbstractGameObject(name), CollisionListener() {}

void BallPlayer::initialize() {
    std::cout << "BallPlayer initialized" << std::endl;

    if (PhysicsManager::getInstance() == nullptr) {
        std::cout << "Creating PhysicsManager" << std::endl;
        PhysicsManager::initialize("PhysicsManager", this);
    }

    this->transformable.setPosition(Game::WINDOW_WIDTH / 4, Game::WINDOW_HEIGHT - 30);

    PlayerInputController* inputController = new PlayerInputController("MyPlayerInput");
    this->attachComponent(inputController);

    PlayerBallMovement* movement = new PlayerBallMovement("MyBallMovement");
    this->attachComponent(movement);

    Renderer* renderer = Renderer::createSprite("PlayerSprite", "eagle");
    attachComponent(renderer);

    sprite = renderer->getSprite(); // Retrieve the sprite
    if (sprite != nullptr) {
        std::cout << "Position: " << sprite->getPosition().x << ":" << sprite->getPosition().y << std::endl;
        this->collider = new Collider("PlayerCollider");
        this->collider->setLocalBounds(sprite->getGlobalBounds());
        std::cout << "BOUNDS: " << sprite->getGlobalBounds().left << ":" << sprite->getGlobalBounds().top << ":" << sprite->getGlobalBounds().width << ":" << sprite->getGlobalBounds().height << std::endl;
    } else {
        std::cerr << "Error: sprite is nullptr" << std::endl;
    }
    this->collider->setCollisionListener(this);
    this->attachComponent(this->collider);

    PhysicsManager* physicsManager = PhysicsManager::getInstance();
    if (physicsManager != nullptr) {
        physicsManager->trackObject(this->collider);
    } else {
        std::cerr << "Error: PhysicsManager instance is not initialized." << std::endl;
    }

}

sf::Sprite* BallPlayer::getSprite() const {
    return sprite;
}

void BallPlayer::processInputs(sf::Event event) {
    AbstractGameObject::processInputs(event);
}

/// <summary>
/// Determines whether or not the player hit the ground.
/// </summary>
/// <param name="deltaTime"></param>
void BallPlayer::update(sf::Time deltaTime) {
    AbstractGameObject::update(deltaTime);
    // Check if the player has reached the ground level
    if (this->getTransformable()->getPosition().y >= 449) {
        if (!isOnGround && collisionExited) {
            std::cout << "Player hit the ground" << std::endl;
            isOnGround = true;
            collisionExited = false;
            UIData* scoreData = UIManager::getInstance()->getUIData(UIManager::SCORE_UI_KEY);
            scoreData->putInt(UIManager::SCORE_UI_KEY, scoreData->getInt(UIManager::SCORE_UI_KEY, 0) - 100);
            scoreData->refreshTextFromData("scoreText", UIManager::SCORE_UI_KEY, "Score: ");
        }
    }
    else {
        isOnGround = false;
    }

}
/// <summary>
/// Sets the player height above a ball object when the player collides with the top of it. 
/// </summary>
/// <param name="contact"></param>

void BallPlayer::onCollisionEnter(AbstractGameObject* contact) {
    if (contact->getName().find("ball") != std::string::npos) {
        std::cout << "Player collided with the ball" << std::endl;
        PlayerBallMovement* movement = dynamic_cast<PlayerBallMovement*>(this->findComponentByName("MyBallMovement"));
        if (movement != nullptr) {
            float ballHeight = dynamic_cast<BallObject*>(contact)->getSprite()->getGlobalBounds().height;
            movement->setPlayerHeight(ballHeight / 2 + 30); 
        }

    }
}
/// <summary>
/// Sets the player height to fall back down to the ground, sets a flag to see if the player exited the collision to see if they just came from a ball.
/// </summary>
/// <param name="gameObject"></param>
void BallPlayer::onCollisionExit(AbstractGameObject* gameObject) {
	std::cout << "PlayerObject exited collision with: " << gameObject->getName() << std::endl;
    PlayerBallMovement* movement = dynamic_cast<PlayerBallMovement*>(this->findComponentByName("MyBallMovement"));
    movement->setPlayerHeight(30);
    collisionExited = true;
	std::cout << "PlayerObject collision exited: " << collisionExited << std::endl;
}

bool BallPlayer::isJumping() const {
    return isJumpingFlag;
}
