#pragma once
#include <unordered_map>
#include "AbstractScene.h"

typedef std::unordered_map<std::string, AbstractScene*> SceneTable;
typedef std::vector<std::string> SceneList;

class SceneManager {
public:
	static std::string MAIN_MENU_SCENE_NAME;
	static std::string GAME_SCENE_NAME;
	static std::string TITLE_SCENE_NAME;
	static std::string BALL_SCENE_NAME;

	static SceneManager* getInstance();
	void registerScene(AbstractScene* scene);
	void loadScene(std::string name);
	void unloadScene();
	bool isSceneLoaded(std::string name);
	void checkLoadScene();

private:
	SceneManager() {};
	SceneManager(SceneManager const&) {};
	SceneManager& operator = (SceneManager const&) {};
	static SceneManager* sharedInstance;

	SceneTable storedScenes;
	AbstractScene* activeScene;
	std::string toLoadSceneName;
	bool isLoading = false;
};