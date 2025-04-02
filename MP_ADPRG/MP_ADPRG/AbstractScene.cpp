#include "AbstractScene.h"
#include "GameObjectManager.h"
#include <iostream>

AbstractScene::AbstractScene(std::string sceneName) {
    this->sceneName = sceneName;
    std::cout << "AbstractScene created with name: " << sceneName << std::endl;
}

void AbstractScene::onUnloadObjects() {
    std::cout << "Unloading objects in scene: " << this->sceneName << std::endl;
    GameObjectManager::getInstance()->deleteAllObjectsInScene();
    std::cout << "Objects unloaded in scene: " << this->sceneName << std::endl;
}

std::string AbstractScene::getSceneName() {
    std::cout << "Getting scene name: " << this->sceneName << std::endl;
    return this->sceneName;
}

void AbstractScene::registerObject(AbstractGameObject* object) {
    std::cout << "Registering object: " << object->getName() << " in scene: " << this->sceneName << std::endl;
    GameObjectManager::getInstance()->addObject(object);
}
