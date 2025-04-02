#include "EnemySwarmHandler.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "EnemyAirplane.h"
#include <iostream>

EnemySwarmHandler::EnemySwarmHandler(int numEnemies, std::string name, AbstractGameObject* parent) : AbstractComponent(name, Script), distribution(1.0f, 5.0f) {
    this->enemyPool = new GameObjectPool(
        ObjectPoolHolder::ENEMY_POOL_TAG,
        new EnemyAirplane("enemy"),
        numEnemies,
        parent
    );
    enemyPool->initialize();
    ObjectPoolHolder::getInstance()->registerObjectPool(enemyPool);
    std::cout << "EnemySwarmHandler [" << name << "] initialized with " << numEnemies << " enemies." << std::endl;

    nextSpawnTime = distribution(generator);
}

EnemySwarmHandler::~EnemySwarmHandler() {
    delete this->enemyPool;
    std::cout << "EnemySwarmHandler [" << name << "] destroyed." << std::endl;
}

void EnemySwarmHandler::perform() {
    GameObjectPool* enemyPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_POOL_TAG);
    this->ticks += this->deltaTime.asSeconds();

    if (this->ticks > SPAWN_INTERVAL) {
        this->ticks = 0.0f;
        enemyPool->requestPoolable();
        nextSpawnTime = distribution(generator);
    }

    std::vector<AbstractPoolable*> toRelease;
    for (auto& enemy : enemyPool->getUsedObjects()) {
        sf::Vector2f position = enemy->getPosition();
        if (position.x < 0) {
            toRelease.push_back(enemy);
        }
    }
    for (auto& enemy : toRelease) {
        enemyPool->releasePoolable(enemy);
    }
}

