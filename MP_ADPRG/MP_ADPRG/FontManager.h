#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

class FontManager
{
public:
	static FontManager* getInstance();

	void loadAll();
	sf::Font* getFont(std::string);
private:
	FontManager() {};
	FontManager(FontManager const&) {};
	static FontManager* sharedInstance;

	void loadFont(std::string, std::string);
	std::unordered_map<std::string, sf::Font*> fontMap;

};