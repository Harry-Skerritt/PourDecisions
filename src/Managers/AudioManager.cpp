#include "AudioManager.h"
#include <iostream>

// Singleton access
AudioManager& AudioManager::getInstance() {
    static AudioManager instance;
    return instance;
}

// Load music
bool AudioManager::loadMusic(const std::string& name, const std::string& filepath) {
    auto music = std::make_unique<sf::Music>();
    if (!music->openFromFile(filepath)) {
        std::cerr << "Failed to load music: " << filepath << std::endl;
        return false;
    }
    musicMap[name] = std::move(music); // Store the unique_ptr
    return true;
}

// Load sound effect
bool AudioManager::loadSoundEffect(const std::string& name, const std::string& filepath) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filepath)) {
        std::cerr << "Failed to load sound effect: " << filepath << std::endl;
        return false;
    }
    soundBuffers[name] = std::move(buffer);

    sf::Sound sound;
    sound.setBuffer(soundBuffers[name]);
    sounds[name] = std::move(sound);
    return true;
}

// Play music
void AudioManager::playMusic(const std::string& name, bool loop) {
    auto it = musicMap.find(name);
    if (it != musicMap.end()) {
        it->second->setLoop(loop);
        it->second->play();
    }
    else {
        std::cerr << "Music not found: " << name << std::endl;
    }
}

// Pause music
void AudioManager::pauseMusic() {
    for (auto& [name, music] : musicMap) {
        if (music->getStatus() == sf::Music::Playing) {
            music->pause();
            break;
        }
    }
}

// Stop music
void AudioManager::stopMusic() {
    for (auto& [name, music] : musicMap) {
        if (music->getStatus() == sf::Music::Playing) {
            music->stop();
            break;
        }
    }
}

// Set music volume
void AudioManager::setMusicVolume(float volume) {
    musicVolume = volume;
    for (auto& [name, music] : musicMap) {
        music->setVolume(musicVolume);
    }
    
}

// Get music volume
float AudioManager::getMusicVolume() {
    return musicVolume;
}



// Play sound effect
void AudioManager::playSoundEffect(const std::string& name, float volume) {
    auto it = sounds.find(name);
    if (it != sounds.end()) {
        it->second.setVolume(volume);
        it->second.play();
    }
    else {
        std::cerr << "Sound effect not found: " << name << std::endl;
    }
}

// Stop all sound effects
void AudioManager::stopAllSoundEffects() {
    for (auto& [name, sound] : sounds) {
        sound.stop();
    }
}

// Set sound effect volume
void AudioManager::setSoundEffectVolume(const std::string& name, float volume) {
    auto it = sounds.find(name);
    if (it != sounds.end()) {
        it->second.setVolume(volume);
    }
    else {
        std::cerr << "Sound effect not found: " << name << std::endl;
    }
}
