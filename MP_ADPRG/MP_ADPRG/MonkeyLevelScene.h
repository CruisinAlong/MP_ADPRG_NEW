// MonkeyLevelScene.h
#pragma once
#include "AbstractScene.h"
#include "MonkeyLevelScreen.h"

class MonkeyLevelScene : public AbstractScene {
public:
    MonkeyLevelScene();
    void onLoadResources() override;
    void onLoadObjects() override;
    void onUnloadObjects() override;
    void onUnloadResources() override;
};


