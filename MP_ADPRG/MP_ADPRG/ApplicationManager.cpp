#include "ApplicationManager.h"

ApplicationManager* ApplicationManager::sharedInstance = NULL;

ApplicationManager* ApplicationManager::getInstance()
{
	if (sharedInstance == nullptr) {
		sharedInstance = new ApplicationManager();
	}
	return sharedInstance;
};

void ApplicationManager::applicationQuit() {
	this->window->close();
}
void ApplicationManager::pauseApplication() {
	this->state = Paused;
}
void ApplicationManager::resumeApplication() {
	this->state = Running;
}
bool ApplicationManager::isPaused() {
	return this->state == Paused;
}

ApplicationManager::~ApplicationManager() {
	delete this->window;
}