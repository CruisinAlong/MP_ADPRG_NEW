#pragma once
#include "AbstractScene.h"

class GameScene : public AbstractScene {
public:
    GameScene();
    void onLoadResources() override;
    void onLoadObjects() override;
    void onUnloadResources() override;
    void onUnloadObjects() override;
};
