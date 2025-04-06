#pragma once
#include "AbstractComponent.h"
#include "GameObjectPool.h"
#include "SlowForwardEnemy.h"
#include <random>

class SlowForwardEnemySwarmHandler : public AbstractComponent {
public:
    SlowForwardEnemySwarmHandler(int numEnemies, std::string name, AbstractGameObject* parent);
    ~SlowForwardEnemySwarmHandler();
    void perform() override;

private:
    GameObjectPool* enemyPool;
    const float SPAWN_INTERVAL = 2.0f;
    float nextSpawnTime = 0.0f;
    float ticks = 0.0f;
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution;
};
