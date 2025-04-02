#include "UIText.h"
#include "FontManager.h"
#include "Renderer.h"
#include <iostream>

UIText::UIText(std::string name) : AbstractGameObject(name) {
    std::cout << "UIText constructor called for: " << name << std::endl;
    this->text = new sf::Text();
}

UIText::~UIText() {
    std::cout << "UIText destructor called for: " << this->getName() << std::endl;
    delete this->text;
}

void UIText::initialize() {
    std::cout << "UIText initialize called for: " << this->getName() << std::endl;
    sf::Font* font = FontManager::getInstance()->getFont("default");
    text->setFont(*font);
    text->setFillColor(sf::Color::White);
    text->setOutlineColor(sf::Color::Black);
    text->setOutlineThickness(4.0f);
    this->setSize(40);
    this->setText("<Using placeholder!>");

    Renderer* renderer = new Renderer("Text");
    renderer->assignDrawable(text);
    this->attachComponent(renderer);
}

void UIText::setText(std::string text) {
    std::cout << "UIText setText called with text: " << text << std::endl;
    this->text->setString(text);
    sf::FloatRect bounds = this->text->getLocalBounds();
    this->text->setOrigin(bounds.width / 2, bounds.height / 2);
}

std::string UIText::getText() {
    std::cout << "UIText getText called" << std::endl;
    return this->text->getString();
}

void UIText::setSize(unsigned int size) {
    std::cout << "UIText setSize called with size: " << size << std::endl;
    this->text->setCharacterSize(size);
}
