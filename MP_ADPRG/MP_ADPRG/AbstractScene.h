#pragma once
#include "AbstractGameObject.h"

class AbstractScene {
public:
	AbstractScene(std::string sceneName);

	virtual void onLoadResources() = 0;
	virtual void onLoadObjects() = 0;

	virtual void onUnloadResources() = 0;
	virtual void onUnloadObjects() = 0;

	std::string getSceneName();

protected:
	void registerObject(AbstractGameObject* object);
	std::string sceneName;
};