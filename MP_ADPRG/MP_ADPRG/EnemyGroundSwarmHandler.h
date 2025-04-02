#pragma once

#include "AbstractComponent.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "EnemyGroundUnit.h"

class EnemyGroundSwarmHandler : public AbstractComponent {
public:
    EnemyGroundSwarmHandler(int numEnemies, std::string name, AbstractGameObject* parent);
    ~EnemyGroundSwarmHandler();

    void perform() override;

private:
    GameObjectPool* enemyPool;
    const float SPAWN_INTERVAL = 0.01f;
    float ticks = 0.0f;
};
