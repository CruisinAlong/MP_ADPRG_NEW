#pragma once
#include "AbstractRendererFactory.h"

class RendererFactory : public AbstractRendererFactory {
public:
	Renderer* createSprite(std::string name, std::string resourceName);
	Renderer* createCircle(std::string name, float radius);		
};