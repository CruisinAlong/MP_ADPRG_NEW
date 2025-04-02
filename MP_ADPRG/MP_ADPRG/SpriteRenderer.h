#pragma once
#include "Renderer.h"
class SpriteRenderer : public Renderer { 
public:
	SpriteRenderer(std::string name, std::string textureName); 
	sf::Sprite* getSprite();
private:
	sf::Sprite* sprite;
};