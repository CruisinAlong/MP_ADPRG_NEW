#include "SoundManager.h"
#include <iostream>

SoundManager* SoundManager::sharedInstance = nullptr;

SoundManager::SoundManager() {
    std::cout << "SoundManager constructor called" << std::endl;
}
/// <summary>
/// Handles BGM for game
/// </summary>
/// <returns></returns>
SoundManager* SoundManager::getInstance() {
    if (sharedInstance == nullptr) {
        sharedInstance = new SoundManager();
    }
    return sharedInstance;
}

void SoundManager::loadAll() {
    loadMusic("Stage1", "Media/Sounds/Stage1.wav");
    loadMusic("Stage2", "Media/Sounds/Stage2.wav");
    loadMusic("Stage3", "Media/Sounds/Stage3.wav");
}

void SoundManager::loadSound(const std::string& key, const std::string& path) {
    sf::SoundBuffer* soundBuffer = new sf::SoundBuffer();
    if (!soundBuffer->loadFromFile(path)) {
        std::cerr << "Failed to load sound: " << path << std::endl;
        delete soundBuffer;
        return;
    }
    soundMap[key] = soundBuffer;
}

void SoundManager::playSound(const std::string& key) {
    if (soundMap.find(key) != soundMap.end() && soundMap[key] != nullptr) {
        sf::Sound sound;
        sound.setBuffer(*soundMap[key]);
        sound.play();
        soundInstances[key] = sound;
    }
    else {
        std::cerr << "Sound not found: " << key << std::endl;
    }
}

void SoundManager::loadMusic(const std::string& key, const std::string& path) {
    std::cout << "Loading music: " << path << std::endl;
    sf::Music* music = new sf::Music();
    if (!music->openFromFile(path)) {
        std::cerr << "Failed to load music: " << path << std::endl;
        delete music;
        return;
    }
    musicMap[key] = music;
}

sf::SoundBuffer* SoundManager::getSound(const std::string& key) {
    if (soundMap.find(key) != soundMap.end() && soundMap[key] != nullptr) {
        return soundMap[key];
    }
    else {
        std::cerr << "Sound not found: " << key << std::endl;
        return nullptr;
    }
}

sf::Music* SoundManager::getMusic(const std::string& key) {
    if (musicMap.find(key) != musicMap.end() && musicMap[key] != nullptr) {
        return musicMap[key];
    }
    else {
        std::cerr << "Music not found: " << key << std::endl;
        return nullptr;
    }
}

void SoundManager::playMusic(const std::string& key) {
    sf::Music* music = getMusic(key);
    if (music != nullptr) {
        if (currentMusic != nullptr) {
            currentMusic->stop();
        }
        currentMusic = music;
        currentMusic->setLoop(true);
        currentMusic->play();
    }
}

void SoundManager::stopMusic() {
    if (currentMusic != nullptr) {
        currentMusic->stop();
        currentMusic = nullptr;
    }
}
