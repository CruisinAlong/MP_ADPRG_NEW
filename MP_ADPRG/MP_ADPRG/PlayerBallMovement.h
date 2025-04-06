#pragma once

#include "PlayerMovement.h"
#include "BallObject.h"

class PlayerBallMovement : public PlayerMovement {
public:
    PlayerBallMovement(std::string name);
    void perform() override;
	void setPlayerHeight(float height);
	bool getIsJumping() const;

private:
    bool isRidingBall;
	bool jumpFlag;
    BallObject* currentBall;
	bool isJumping;
	float jumpSpeed;
	float gravity;
	float velocityY;
	float playerHeight;
};


