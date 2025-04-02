#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>


class Reader {
public:
	Reader();
	void ReadFPS(sf::Font font);
	sf::Text* getText();
private:
	float fps;
	sf::Clock clock;
	sf::Time previousTime;
	sf::Time currentTime;
	sf::Font mFont;
	sf::Text mText;
};