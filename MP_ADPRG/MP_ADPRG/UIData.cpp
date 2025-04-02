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
