#pragma once
#include "AbstractComponent.h"
#include "GameObjectPool.h"
#include <random>

class EnemySwarmHandler : public AbstractComponent {
public:
	EnemySwarmHandler(int numEnemies, std::string name, AbstractGameObject* parent);
	~EnemySwarmHandler();
	void perform();
private:
    GameObjectPool* enemyPool;
    const float SPAWN_INTERVAL = 3.0f;
    float nextSpawnTime = 0.0f;
    float ticks = 0.0f;
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution;
};