#pragma once
#include <unordered_map>
#include "UIText.h"
#include "UIButton.h"
#include "UIData.h"

typedef std::unordered_map<std::string, UIData*> DataTable;

class UIManager {
public:
	static const string SCORE_UI_KEY;

	static UIManager* getInstance();

	UIData* getUIData(string name);
	UIData* storeData(string name);
	void removeData(string name);

private:
	UIManager() {};
	UIManager(UIManager const&) {};
	UIManager& operator=(UIManager const&) {};
	static UIManager* sharedInstance;

	DataTable dataTable;
};