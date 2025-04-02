#pragma once
#include "AbstractGameObject.h"
#include "ButtonListener.h"

class UIButton : public AbstractGameObject {
public:
	UIButton(std::string name, sf::Texture* normalTexture, sf::Texture* pressedTexture);
	void initialize();
	void changeButtonToNormal();
	void changeButtonToPressed();
	sf::FloatRect getLocalBounds();
	sf::FloatRect getGlobalBounds();
	void setButtonListener(ButtonListener* listener);
private:
	sf::Texture* normalTexture;
	sf::Texture* pressedTexture;
	ButtonListener* listener;
};