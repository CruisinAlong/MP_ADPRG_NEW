#include "EnemyGroundSwarmHandler.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "EnemyGroundUnit.h"
#include <iostream>

EnemyGroundSwarmHandler::EnemyGroundSwarmHandler(int numEnemies, std::string name, AbstractGameObject* parent) : AbstractComponent(name, Script) {
    this->enemyPool = new GameObjectPool(
        ObjectPoolHolder::GROUND_POOL_TAG,
        new EnemyGroundUnit("enemyGroundUnit"),
        numEnemies,
        parent
    );
    enemyPool->initialize();
    ObjectPoolHolder::getInstance()->registerObjectPool(enemyPool);
    std::cout << "EnemyGroundSwarmHandler [" << name << "] initialized with " << numEnemies << " enemies." << std::endl;
}

EnemyGroundSwarmHandler::~EnemyGroundSwarmHandler() {
    delete this->enemyPool;
    std::cout << "EnemyGroundSwarmHandler [" << name << "] destroyed." << std::endl;
}

void EnemyGroundSwarmHandler::perform() {
    GameObjectPool* enemyGroundPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::GROUND_POOL_TAG);
    this->ticks += this->deltaTime.asSeconds();

    if (this->ticks > SPAWN_INTERVAL) {
        this->ticks = 0.0f;
        enemyGroundPool->requestPoolable();

    }

    std::vector<AbstractPoolable*> toRelease;
    for (auto& enemy : enemyGroundPool->getUsedObjects()) {
        sf::Vector2f position = enemy->getPosition();
        if (position.x < 0 || position.x > 800) {
            toRelease.push_back(enemy);
            std::cout << "EnemyGroundSwarmHandler [" << name << "] releasing enemy at position: (" << position.x << ", " << position.y << ")" << std::endl;
        }
    }
    for (auto& enemy : toRelease) {
        enemyGroundPool->releasePoolable(enemy);
    }
}

