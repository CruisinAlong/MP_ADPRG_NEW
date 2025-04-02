#pragma once

#include "AbstractComponent.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "EnemyGroundUnit.h"
#include <random>

class EnemyGroundSwarmHandler : public AbstractComponent {
public:
    EnemyGroundSwarmHandler(int numEnemies, std::string name, AbstractGameObject* parent);
    ~EnemyGroundSwarmHandler();

    void perform() override;

private:
    GameObjectPool* enemyPool;
    const float SPAWN_INTERVAL = 2.0f; 
    float nextSpawnTime = 0.0f;
    float ticks = 0.0f;
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution;
};
