// BallObjectHandler.h
#pragma once

#include "AbstractComponent.h"
#include "GameObjectPool.h"
#include "BallObject.h"
#include <random>

class BallObjectHandler : public AbstractComponent {
public:
    BallObjectHandler(int numBalls, std::string name, AbstractGameObject* parent);
    ~BallObjectHandler();

    void perform() override;

private:
    GameObjectPool* ballPool;
    const float SPAWN_INTERVAL = 2.0f; 
    float nextSpawnTime = 0.0f;
    float ticks = 0.0f;
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution;
};

