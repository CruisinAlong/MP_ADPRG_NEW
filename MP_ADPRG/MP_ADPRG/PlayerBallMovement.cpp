#include "PlayerBallMovement.h"
#include "BallPlayer.h"
#include "PhysicsManager.h"
#include "Game.h"

PlayerBallMovement::PlayerBallMovement(std::string name) 
    : PlayerMovement(name), isRidingBall(false), currentBall(nullptr), isJumping(false), jumpSpeed(300.0f), gravity(500.0f), velocityY(0.0f), playerHeight(30.0f) {}
/// <summary>
/// Movement for player when they are in the ball level.
/// </summary>
void PlayerBallMovement::perform() {
    BallPlayer* player = (BallPlayer*)this->getOwner();
    PlayerInputController* inputController = (PlayerInputController*)(player->getComponentsOfType(ComponentType::Input)[0]);
    sf::Transformable* playerTransformable = player->getTransformable(); 
    if (playerTransformable == nullptr || inputController == nullptr) {
        std::cout << "PlayerMovement [" << name << "] error: playerTransformable or inputController not found." << std::endl;
        return;
    }

    sf::Vector2f offset(0.0f, 0.0f);



    if (inputController->isJump() && !isJumping) {
        isJumping = true;
        velocityY = -jumpSpeed;


    }

    if (isJumping) {
        velocityY += gravity * this->deltaTime.asSeconds();
        playerTransformable->move(0, velocityY * this->deltaTime.asSeconds());
        jumpFlag = inputController->isJump();
        if (playerTransformable->getPosition().y >= Game::WINDOW_HEIGHT - playerHeight) {
            playerTransformable->setPosition(playerTransformable->getPosition().x, Game::WINDOW_HEIGHT - playerHeight);
            isJumping = false;
            velocityY = 0.0f;
        }
    }
}

void PlayerBallMovement::setPlayerHeight(float height) {
    playerHeight = height;
}

bool PlayerBallMovement::getIsJumping() const {
	std::cout << "PlayerBallMovement::getIsJumping called, isJumping: " << isJumping << std::endl;
    return jumpFlag;
}



