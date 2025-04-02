#include "UIManager.h"


UIManager* UIManager::sharedInstance = nullptr;

const string UIManager::SCORE_UI_KEY = "score";

UIManager* UIManager::getInstance() {
	if (sharedInstance == nullptr) {
		sharedInstance = new UIManager();
	}
	return sharedInstance;
}

UIData* UIManager::getUIData(string name) {
	return this->dataTable[name];
}

UIData* UIManager::storeData(string name) {
	if (this->dataTable[name] != nullptr) {
		return this->dataTable[name];
	}

	UIData* data = new UIData();
	this->dataTable[name] = data;
	return data;
}

void UIManager::removeData(string name) {
	delete this->dataTable[name];
	this->dataTable.erase(name);
}