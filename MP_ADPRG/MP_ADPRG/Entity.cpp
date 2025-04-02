#include "Entity.h"

Entity::Entity() {};

void Entity::setTexture(sf::Texture texture)
{
	mTexture = texture;
	mSprite.setTexture(mTexture);
}

sf::Sprite* Entity::getSprite()
{
	return &mSprite;
}

Entity* Entity::createEntity(sf::Texture* tex, float x, float y)
{
	Entity* entity = new Entity();
	entity->mSprite.setTexture(*tex);
	entity->mSprite.setPosition(x, y);
	return entity;
}