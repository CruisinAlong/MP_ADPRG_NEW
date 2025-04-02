// MainMenuScene.h
#pragma once
#include "AbstractScene.h"

class MainMenuScene : public AbstractScene
{
public:
	MainMenuScene();

	void onLoadResources() override;
	void onLoadObjects() override;
	void onUnloadResources() override;
	void onUnloadObjects() override; 
};
