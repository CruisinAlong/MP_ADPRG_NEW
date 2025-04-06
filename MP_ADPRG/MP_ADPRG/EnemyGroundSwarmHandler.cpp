#include "EnemyGroundSwarmHandler.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "EnemyGroundUnit.h"
#include <iostream>
/// <summary>
/// Makes ground enemies
/// </summary>
/// <param name="numEnemies"></param>
/// <param name="name"></param>
/// <param name="parent"></param>
EnemyGroundSwarmHandler::EnemyGroundSwarmHandler(int numEnemies, std::string name, AbstractGameObject* parent) : AbstractComponent(name, Script), distribution(1.0f, 5.0f) {
    this->enemyPool = new GameObjectPool(
        ObjectPoolHolder::GROUND_POOL_TAG,
        new EnemyGroundUnit("enemyGroundUnit"),
        numEnemies,
        parent
    );
    enemyPool->initialize();
    ObjectPoolHolder::getInstance()->registerObjectPool(enemyPool);
    std::cout << "EnemyGroundSwarmHandler [" << name << "] initialized with " << numEnemies << " enemies." << std::endl;

    nextSpawnTime = distribution(generator); 
}

EnemyGroundSwarmHandler::~EnemyGroundSwarmHandler() {
    delete this->enemyPool;
    std::cout << "EnemyGroundSwarmHandler [" << name << "] destroyed." << std::endl;
}

void EnemyGroundSwarmHandler::perform() {
    GameObjectPool* enemyGroundPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::GROUND_POOL_TAG);
    this->ticks += this->deltaTime.asSeconds();

    if (this->ticks > nextSpawnTime) {
        this->ticks = 0.0f;
        enemyGroundPool->requestPoolable();

        nextSpawnTime = distribution(generator); 
    }

    std::vector<AbstractPoolable*> toRelease;
    for (auto& enemy : enemyGroundPool->getUsedObjects()) {
        sf::Vector2f position = enemy->getPosition();
        if (position.x < 0 || position.x > 800) {
            toRelease.push_back(enemy);
        }
    }
    for (auto& enemy : toRelease) {
        enemyGroundPool->releasePoolable(enemy);
    }
}

