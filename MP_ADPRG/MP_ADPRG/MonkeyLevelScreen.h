// MonkeyLevelScreen.h
#pragma once
#include "AbstractGameObject.h"
#include "UIText.h"
#include "UIButton.h"
#include "BGObject.h"
#include "HUD.h"
#include "AirplanePlayer.h"
#include "EnemySwarmHandler.h"
#include "EnemyGroundSwarmHandler.h"
#include <SFML/Graphics.hpp>

class MonkeyLevelScreen : public AbstractGameObject {
public:
    MonkeyLevelScreen(std::string name);
    void initialize() override;
    void update(sf::Time deltaTime) override;

    void activateCooldown();
    void resetCooldownTimer();

private:
    void endLevel();
    void startNextLevel();

    BGObject* bgObject;
    HUD* hud;
    UIText* scoreText;
    sf::Time scoreIncrementTimer; // Timer for score increment
    sf::Time cooldownTimer; // Timer for cooldown
    const sf::Time scoreIncrementInterval = sf::seconds(1); // Interval for score increment
    const sf::Time cooldownDuration = sf::seconds(3); // Duration of cooldown after hitting a monkey
    bool isCooldownActive = false;
    sf::Time endLevelTimer; // Timer for end level delay
    const sf::Time endLevelDelay = sf::seconds(5); // Delay duration
    bool endLevelLoaded = false;
};


