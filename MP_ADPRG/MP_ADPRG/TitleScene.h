#pragma once
#include "AbstractScene.h"

class TitleScene : public AbstractScene {
public:
    TitleScene();
    void onLoadResources() override;
    void onLoadObjects() override;
    void onUnloadResources() override;
    void onUnloadObjects() override;
};
