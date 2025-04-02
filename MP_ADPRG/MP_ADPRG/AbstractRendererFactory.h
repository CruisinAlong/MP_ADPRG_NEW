#pragma once
#include "Renderer.h"

class AbstractRendererFactory {
public:
	virtual Renderer* createSprite(std::string name, std::string resourceName) = 0;
	virtual Renderer* createCircle(std::string name, float radius) = 0;
};