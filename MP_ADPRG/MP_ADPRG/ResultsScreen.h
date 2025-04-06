// ResultsScreen.h
#pragma once
#include "AbstractGameObject.h"
#include "UIText.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>

class ResultsScreen : public AbstractGameObject {
public:
    ResultsScreen(std::string name);
    void initialize() override;

private:
    UIText* endLevelText;
    sf::Sprite* resultsBgSprite;
};

