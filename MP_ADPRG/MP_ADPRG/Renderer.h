#pragma once
#include "AbstractComponent.h"

#include <SFML/Graphics.hpp>

class SpriteRenderer;

class Renderer : public AbstractComponent
{
public:
	Renderer(std::string name);
	~Renderer();
	void assignTargetWindow(sf::RenderWindow* window);
	void assignDrawable(sf::Drawable* drawable);
	void setRenderStates(sf::RenderStates renderStates);

	void perform() override;
	
	static Renderer* createSprite(std::string name, std::string resourceName);

private:
	sf::RenderWindow* targetWindow;
	sf::Drawable* drawable;
	sf::RenderStates renderStates;
};
