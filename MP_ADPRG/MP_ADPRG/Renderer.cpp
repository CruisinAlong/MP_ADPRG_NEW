#include "Renderer.h"
#include "SpriteRenderer.h"


Renderer::Renderer(std::string name) : AbstractComponent(name, AbstractComponent::Renderer) {
	this->renderStates = sf::RenderStates::Default;
	this->drawable = nullptr;
	this->targetWindow = nullptr;
}

Renderer::~Renderer() {
	AbstractComponent::~AbstractComponent();
}

void Renderer::assignTargetWindow(sf::RenderWindow* window) {
	this->targetWindow = window;
}

void Renderer::assignDrawable(sf::Drawable* drawable) {
	this->drawable = drawable;
}

void Renderer::setRenderStates(sf::RenderStates renderStates) {
	this->renderStates = renderStates;
}

void Renderer::perform() {
	this->targetWindow->draw(*this->drawable, this->renderStates);
}

Renderer* Renderer::createSprite(std::string name, std::string resourceName) {
	return new SpriteRenderer(name, resourceName);
}
