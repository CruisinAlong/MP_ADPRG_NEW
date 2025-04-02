#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
public:
	Entity();
	void setTexture(sf::Texture texture);
	sf::Sprite* getSprite();

	static Entity* createEntity(sf::Texture* tex, float x, float y);
private:
	sf::Texture mTexture;
	sf::Sprite mSprite;

};