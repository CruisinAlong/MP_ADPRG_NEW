#include "SceneManager.h"
#include <iostream>

std::string SceneManager::MAIN_MENU_SCENE_NAME = "MainMenuScene";
std::string SceneManager::GAME_SCENE_NAME = "GameScene";
std::string SceneManager::TITLE_SCENE_NAME = "TitleScene";

SceneManager* SceneManager::sharedInstance = nullptr;

using namespace std;

SceneManager* SceneManager::getInstance() {
	if (sharedInstance == nullptr) {
		sharedInstance = new SceneManager();
		cout << "SceneManager instance created" << endl;
	}
	return sharedInstance;
}

void SceneManager::registerScene(AbstractScene* scene) {
	cout << "Registering scene: " << scene->getSceneName() << endl;
	this->storedScenes[scene->getSceneName()] = scene;
	cout << "Scene registered: " << scene->getSceneName() << endl;
}

void SceneManager::checkLoadScene() {
	if (this->isLoading) {
		cout << "Loading scene: " << this->toLoadSceneName << endl;
		this->unloadScene();
		this->activeScene = this->storedScenes[this->toLoadSceneName];
		this->activeScene->onLoadObjects();
		this->activeScene->onLoadResources();
		this->isLoading = false;
		cout << "Scene loaded: " << this->toLoadSceneName << endl;
	}
}

void SceneManager::loadScene(std::string name) {
	cout << "Request to load scene: " << name << endl;
	this->isLoading = true;
	this->toLoadSceneName = name;
}

void SceneManager::unloadScene() {
	if (this->activeScene != nullptr) {
		cout << "Unloading scene: " << this->activeScene->getSceneName() << endl;
		this->activeScene->onUnloadObjects();
		this->activeScene->onUnloadResources();
		cout << "Scene unloaded: " << this->activeScene->getSceneName() << endl;
	}
}

bool SceneManager::isSceneLoaded(std::string name) {
	bool loaded = this->storedScenes.find(name) != this->storedScenes.end();
	cout << "Is scene loaded (" << name << "): " << (loaded ? "Yes" : "No") << endl;
	return loaded;
}

