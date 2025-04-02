#pragma once
#include "AbstractGameObject.h"


class EmptyGameObject : public AbstractGameObject {
public:
	EmptyGameObject(std::string name);
	void initialize();
};