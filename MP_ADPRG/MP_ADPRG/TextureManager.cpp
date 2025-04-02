#include <stddef.h>
#include <iostream>
#include "TextureManager.h"

TextureManager* TextureManager::sharedInstance = nullptr;

TextureManager::TextureManager()
{
    std::cout << "TextureManager constructor called" << std::endl;
}

TextureManager* TextureManager::getInstance()
{
    if (sharedInstance == nullptr) {
        sharedInstance = new TextureManager();
    }
    return sharedInstance;
}

void TestFunction()
{
    std::cout << "Test function called" << std::endl;
}

void TextureManager::loadAll()
{
    loadTexture("desert_bg", "Media/Textures/Desert.png");
    sf::Texture* bgTex;
    bgTex = getTexture("desert_bg");
    if (bgTex != nullptr) {
        bgTex->setRepeated(true);
    }
    loadTexture("eagle", "Media/Textures/Eagle.png");
    loadTexture("raptor", "Media/Textures/Raptor.png");
    loadTexture("raptor", "Media/Textures/Raptor.png");
    loadTexture("avenger", "Media/Textures/Avenger.png");
    loadTexture("title_bg", "Media/Textures/f.png");
    loadTexture("btn_normal", "Media/Textures/b_4.png");
    loadTexture("btn_pressed", "Media/Textures/b_5.png");
    loadTexture("HUD_bg", "Media/Textures/bar_1.png");
    loadTexture("bullet", "Media/Textures/Bullet.png");
    loadTexture("main_menu_bg", "Media/Textures/TitleScreenBG.png");
}

void TextureManager::loadTexture(std::string key, std::string path)
{
    sf::Texture* texture = new sf::Texture();
    if (!texture->loadFromFile(path)) {
        std::cerr << "Failed to load texture: " << path << std::endl;
        delete texture;
        return;
    }
    textureMap[key] = texture;
}

sf::Texture* TextureManager::getTexture(std::string key)
{
    if (textureMap[key] != nullptr) {
        return textureMap[key];
    }
    else {
        std::cerr << "Texture not found: " << key << std::endl;
        return nullptr;
    }
}

