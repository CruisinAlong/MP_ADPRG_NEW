// BallObjectHandler.cpp
#include "BallObjectHandler.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "BallObject.h"
#include <iostream>

BallObjectHandler::BallObjectHandler(int numBalls, std::string name, AbstractGameObject* parent)
    : AbstractComponent(name, Script), distribution(1.0f, 5.0f) { 
    this->ballPool = new GameObjectPool(
        ObjectPoolHolder::BALL_POOL_TAG,
        new BallObject("ball"),
        numBalls,
        parent
    );
    ballPool->initialize();
    ObjectPoolHolder::getInstance()->registerObjectPool(ballPool);
    std::cout << "BallObjectHandler [" << name << "] initialized with " << numBalls << " balls." << std::endl;

    // Initialize the next spawn time
    nextSpawnTime = distribution(generator);
}

BallObjectHandler::~BallObjectHandler() {
    delete this->ballPool;
    std::cout << "BallObjectHandler [" << name << "] destroyed." << std::endl;
}

void BallObjectHandler::perform() {
    GameObjectPool* ballPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::BALL_POOL_TAG);
    this->ticks += this->deltaTime.asSeconds();

    if (this->ticks > nextSpawnTime) {
        this->ticks = 0.0f;
        ballPool->requestPoolable();

        // Set the next spawn time to a random value
        nextSpawnTime = distribution(generator);
    }

    std::vector<AbstractPoolable*> toRelease;
    for (auto& ball : ballPool->getUsedObjects()) {
        sf::Vector2f position = ball->getPosition();
        if (position.x < 0 || position.x > 800) {
            toRelease.push_back(ball);
        }
    }
    for (auto& ball : toRelease) {
        ballPool->releasePoolable(ball);
    }
}

