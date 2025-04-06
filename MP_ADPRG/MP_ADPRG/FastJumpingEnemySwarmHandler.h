// FastJumpingEnemySwarmHandler.h
#pragma once
#include "AbstractComponent.h"
#include "GameObjectPool.h"
#include "FastJumpingEnemy.h"
#include <random>

class FastJumpingEnemySwarmHandler : public AbstractComponent {
public:
    FastJumpingEnemySwarmHandler(int numEnemies, std::string name, AbstractGameObject* parent);
    ~FastJumpingEnemySwarmHandler();
    void perform() override;

private:
    GameObjectPool* enemyPool;
    const float SPAWN_INTERVAL = 2.0f;
    float nextSpawnTime = 0.0f;
    float ticks = 0.0f;
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution;
};



