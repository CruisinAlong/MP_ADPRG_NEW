#include "FontManager.h"
#include <iostream>

FontManager* FontManager::sharedInstance = NULL;

FontManager* FontManager::getInstance() {
    if (sharedInstance == NULL) {
        sharedInstance = new FontManager();
    }
    return sharedInstance;
}

void FontManager::loadAll() {
    loadFont("default", "Media/Fonts/Sansation.ttf");
}

void FontManager::loadFont(std::string key, std::string path) {
    std::cout << "Loading font with key: " << key << " from path: " << path << std::endl;
    sf::Font* font = new sf::Font();
    if (font->loadFromFile(path)) {
        fontMap[key] = font;
        std::cout << "Font loaded successfully for key: " << key << std::endl;
    }
    else {
        std::cout << "Failed to load font from path: " << path << std::endl;
        delete font;
    }
}

sf::Font* FontManager::getFont(std::string key) {
    std::cout << "Retrieving font with key: " << key << std::endl;
    if (fontMap[key] != NULL) {
        return fontMap[key];
    }
    else {
        std::cout << "No font found for key: " << key << std::endl;
        return NULL;
    }
}
