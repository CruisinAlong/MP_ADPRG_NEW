#include "UIData.h"
#include <iostream>

UIData::~UIData() {
	this->textTable.clear();	
}
void UIData::putInt(string key, int value) {
	this->intTable[key] = value;
}
void UIData::putFloat(string key, float value) {
	this->floatTable[key] = value;
}
int UIData::getInt(string key, int defaultVal) {
	if (this->intTable.count(key) != 0) {
		return this->intTable[key];
	}
	else {
		return defaultVal;
	}
}
float UIData::getFloat(string key, float defaultVal) {
	if (this->floatTable.count(key) != 0) {
		return this->floatTable[key];
	}
	else {
		return defaultVal;
	}
}

void UIData::bindUIText(UIText* text) {
	this->textTable[text->getName()] = text;
}

void UIData::refreshTextFromData(std::string objectName, std::string key, std::string prefix) {
	if (textTable.find(objectName) != textTable.end()) {
		UIText* text = textTable[objectName];
		if (intTable.find(key) != intTable.end()) {
			text->setText(prefix + std::to_string(intTable[key]));
		}
		else if (floatTable.find(key) != floatTable.end()) {
			text->setText(prefix + std::to_string(floatTable[key]));
		}
		else {
			std::cerr << "Key not found in data tables: " << key << std::endl;
		}
	}
	else {
		std::cerr << "UIText object not found: " << objectName << std::endl;
	}
}	

