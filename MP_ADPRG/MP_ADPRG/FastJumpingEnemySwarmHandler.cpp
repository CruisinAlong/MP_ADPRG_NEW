// FastJumpingEnemySwarmHandler.cpp
#include "FastJumpingEnemySwarmHandler.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "FastJumpingEnemy.h"
#include <iostream>

FastJumpingEnemySwarmHandler::FastJumpingEnemySwarmHandler(int numEnemies, std::string name, AbstractGameObject* parent) : AbstractComponent(name, Script), distribution(1.0f, 5.0f) {
    this->enemyPool = new GameObjectPool(
        ObjectPoolHolder::MONKEY_POOL_TAG,
        new FastJumpingEnemy("fastJumpingEnemy"),
        numEnemies,
        parent
    );
    enemyPool->initialize();
    ObjectPoolHolder::getInstance()->registerObjectPool(enemyPool);
    std::cout << "FastJumpingEnemySwarmHandler [" << name << "] initialized with " << numEnemies << " enemies." << std::endl;

    nextSpawnTime = distribution(generator); 
}

FastJumpingEnemySwarmHandler::~FastJumpingEnemySwarmHandler() {
    delete this->enemyPool;
    std::cout << "FastJumpingEnemySwarmHandler [" << name << "] destroyed." << std::endl;
}

void FastJumpingEnemySwarmHandler::perform() {
    GameObjectPool* fastJumpingEnemyPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::MONKEY_POOL_TAG);
    this->ticks += this->deltaTime.asSeconds();

    if (this->ticks > nextSpawnTime) {
        this->ticks = 0.0f;
        fastJumpingEnemyPool->requestPoolable();

        nextSpawnTime = distribution(generator); 
    }

    std::vector<AbstractPoolable*> toRelease;
    for (auto& enemy : fastJumpingEnemyPool->getUsedObjects()) {
        sf::Vector2f position = enemy->getPosition();
        if (position.x < 0 || position.x > 800) {
            toRelease.push_back(enemy);
        }
    }
    for (auto& enemy : toRelease) {
        fastJumpingEnemyPool->releasePoolable(enemy);
    }
}



