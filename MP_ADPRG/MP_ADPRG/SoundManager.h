#pragma once
#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>

class SoundManager {
public:
    static SoundManager* getInstance();
    void loadAll();
    void loadSound(const std::string& key, const std::string& path);
    void loadMusic(const std::string& key, const std::string& path);
    void playMusic(const std::string& key);
    void playSound(const std::string& key);
    void stopMusic();

private:
    SoundManager();
    static SoundManager* sharedInstance;
    std::unordered_map<std::string, sf::SoundBuffer*> soundMap;
    std::unordered_map<std::string, sf::Music*> musicMap;
    std::unordered_map<std::string, sf::Sound> soundInstances;
    sf::Music* currentMusic = nullptr;

    sf::SoundBuffer* getSound(const std::string& key);
    sf::Music* getMusic(const std::string& key);
};
