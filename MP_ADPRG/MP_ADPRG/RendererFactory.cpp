#include "RendererFactory.h"
#include "SpriteRenderer.h"

Renderer* RendererFactory::createSprite(std::string name, std::string resourceName) {
	return SpriteRenderer::createSprite(name, resourceName);

}

Renderer* RendererFactory::createCircle(std::string name, float radius) {
	Renderer* renderer = new Renderer(name);
	sf::CircleShape* drawable = new sf::CircleShape(radius);
	drawable->setOrigin(radius, radius);
	renderer->assignDrawable(drawable);
	return renderer;
}