#include "SlowForwardEnemySwarmHandler.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "SlowForwardEnemy.h"
#include <iostream>

SlowForwardEnemySwarmHandler::SlowForwardEnemySwarmHandler(int numEnemies, std::string name, AbstractGameObject* parent) : AbstractComponent(name, Script), distribution(1.0f, 5.0f) {
    this->enemyPool = new GameObjectPool(
        ObjectPoolHolder::SLOW_FORWARD_POOL_TAG,
        new SlowForwardEnemy("slowForwardEnemy"),
        numEnemies,
        parent
    );
    enemyPool->initialize();
    ObjectPoolHolder::getInstance()->registerObjectPool(enemyPool);
    std::cout << "SlowForwardEnemySwarmHandler [" << name << "] initialized with " << numEnemies << " enemies." << std::endl;

    nextSpawnTime = distribution(generator); 
}

SlowForwardEnemySwarmHandler::~SlowForwardEnemySwarmHandler() {
    delete this->enemyPool;
    std::cout << "SlowForwardEnemySwarmHandler [" << name << "] destroyed." << std::endl;
}

void SlowForwardEnemySwarmHandler::perform() {
    GameObjectPool* slowForwardEnemyPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::SLOW_FORWARD_POOL_TAG);
    this->ticks += this->deltaTime.asSeconds();

    if (this->ticks > nextSpawnTime) {
        this->ticks = 0.0f;
        slowForwardEnemyPool->requestPoolable();

        nextSpawnTime = distribution(generator); 
    }

    std::vector<AbstractPoolable*> toRelease;
    for (auto& enemy : slowForwardEnemyPool->getUsedObjects()) {
        sf::Vector2f position = enemy->getPosition();
        if (position.x < 0 || position.x > 800) {
            toRelease.push_back(enemy);
        }
    }
    for (auto& enemy : toRelease) {
        slowForwardEnemyPool->releasePoolable(enemy);
    }
}
