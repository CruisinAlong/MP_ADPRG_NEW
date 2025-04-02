// BallScene.h
#pragma once

#include "AbstractScene.h"

class BallScene : public AbstractScene {
public:
    BallScene();
    void onLoadResources() override;
    void onLoadObjects() override;
    void onUnloadResources() override;
    void onUnloadObjects() override;
};
